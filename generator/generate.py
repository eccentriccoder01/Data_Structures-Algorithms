import json
import os
import re
from pathlib import Path

from google import genai

ROOT = Path(__file__).resolve().parents[1]
GEN_DIR = ROOT / "generator"
DAILY_DIR = ROOT / "daily"
STATE_FILE = GEN_DIR / "state.json"

NUM_ARTICLES_PER_DAY = 10
MODEL_NAME = "gemini-2.5-flash"


# -------------------------------------------------------------
# Load & Save State
# -------------------------------------------------------------
def load_state():
    if STATE_FILE.exists():
        return json.loads(STATE_FILE.read_text(encoding="utf-8"))
    return {"day": 1, "used_slugs": []}


def save_state(state):
    STATE_FILE.write_text(json.dumps(state, indent=2), encoding="utf-8")


# -------------------------------------------------------------
# Helpers
# -------------------------------------------------------------
def slugify(title: str) -> str:
    s = title.lower()
    s = re.sub(r"[^a-z0-9]+", "_", s)
    s = re.sub(r"(^_+|_+$)", "", s)
    return s or "topic"


def b64_to_str(value: str) -> str:
    if not isinstance(value, str) or not value:
        return ""
    try:
        return base64.b64decode(value).decode("utf-8", errors="replace")
    except Exception:
        # In case Gemini messes up base64, fall back to raw
        return value

def build_prompt(used_slugs):
    return f"""
You are generating {NUM_ARTICLES_PER_DAY} medium-length, strictly professional articles on
classic Data Structures and Algorithms for a GitHub knowledge base.

Requirements:
- Domain: ONLY core DSA and algorithms (arrays, linked lists, stacks, queues, trees, heaps,
  hash tables, tries, graphs, greedy, dynamic programming, recursion, divide & conquer,
  segment trees, Fenwick tree, string algorithms like KMP, Z, suffix array, number theory, etc.).
- Exclude: system design, ML, OS, DBMS, web dev, networking, etc.
- Audience: competitive programmers and software engineers preparing for interviews.
- Tone: professional, precise, no emojis, no em/long dashes, no casual language.
- Depth: medium-level detail.

Topic rules:
- Generate exactly {NUM_ARTICLES_PER_DAY} DISTINCT topics.
- Include ALL logically relevant approaches.
- Each topic must be NEW and must NOT correspond to any of these previously used slugs:
  {used_slugs}
- Topics must be focused (e.g., Binary Search, KMP, Dijkstra).
- Every approach must have:
  - A clear explanation.
  - C++, Java, and Python code.

IMPORTANT ENCODING RULE:
- ALL text fields in the JSON MUST be base64-encoded UTF-8 strings.
- This includes titles, explanations, diagrams, code, and complexity sections.
- Use standard base64 with no newlines.

For each topic, return the following JSON structure:

{{
  "title_b64": "<base64(title)>",
  "intro_b64": "<base64(intro)>",
  "use_cases_b64": "<base64(use_cases)>",
  "ascii_diagram_b64": "<base64(ascii_diagram)>",
  "approaches": [
    {{
      "name_b64": "<base64(approach_name)>",
      "explanation_b64": "<base64(approach_explanation)>",
      "cpp_b64": "<base64(cpp_code)>",
      "java_b64": "<base64(java_code)>",
      "python_b64": "<base64(python_code)>"
    }}
  ],
  "complexity_b64": "<base64(complexity_discussion)>"
}}

Details for each field:
- title_b64: short, precise name of the algorithm or data structure.
- intro_b64: 1–2 paragraphs explaining what the topic is.
- use_cases_b64: real-world or interview-style scenarios where this is used.
- ascii_diagram_b64: an ASCII representation of the structure or process when applicable;
  if not applicable, use a minimal schematic or short note.
- approaches: an array of one or more approaches. Each MUST have:
  - name_b64: for example "Brute Force", "Two-Pointer Optimized", "Dynamic Programming (Bottom-Up)".
  - explanation_b64: 1–3 paragraphs explaining how that approach works and its idea.
  - cpp_b64 / java_b64 / python_b64: clean, compilable code for that approach.
- complexity_b64: summary of time and space complexity for the main approaches.

OUTPUT FORMAT:
- Respond with a single JSON array of exactly {NUM_ARTICLES_PER_DAY} such objects.
- The JSON must be valid and directly parseable by json.loads in Python.
- Do NOT include any markdown, code fences, comments, or extra text.
    """.strip()


# -------------------------------------------------------------
# Gemini API Call
# -------------------------------------------------------------

def fix_json_string(text: str) -> str:
    """
    Attempts to fix common JSON formatting issues from LLM output:
    - Unescaped backslashes in code
    - Stray control characters
    - Accidental newlines inside string literals
    """

    # Remove BOM or weird unicode
    text = text.encode("utf-8", "ignore").decode("utf-8")

    # Escape single backslashes: \ → \\ 
    # BUT do NOT double-escape already escaped ones.
    text = re.sub(r'(?<!\\)\\(?![\\nrt"\'/])', r'\\\\', text)

    # Remove trailing commas: },] → } ] 
    text = re.sub(r',(\s*[}\]])', r'\1', text)

    return text

def call_gemini(prompt: str):
    api_key = os.environ.get("GEMINI_API_KEY")
    if not api_key:
        raise RuntimeError("GEMINI_API_KEY environment variable is not set")

    client = genai.Client(api_key=api_key)

    response = client.models.generate_content(
        model=MODEL_NAME,
        contents=prompt,
    )

    text = response.text.strip()

    # Clean accidental fenced code blocks
    if text.startswith("```"):
        text = re.sub(r"^```[a-zA-Z]*", "", text).strip()
        if text.endswith("```"):
            text = text[:-3].strip()

    # FIX JSON HERE
    text = fix_json_string(text)

    # Load JSON
    data = json.loads(text)

    if not isinstance(data, list):
        raise ValueError("Gemini response is not a JSON array")

    if len(data) != NUM_ARTICLES_PER_DAY:
        raise ValueError(
            f"Expected {NUM_ARTICLES_PER_DAY} articles, got {len(data)}"
        )

    return data


# -------------------------------------------------------------
# Markdown Renderer (base64 → Markdown with collapsible code)
# -------------------------------------------------------------
def render_markdown(article: dict) -> str:
    title = b64_to_str(article.get("title_b64", "")).strip()
    intro = b64_to_str(article.get("intro_b64", "")).strip()
    use_cases = b64_to_str(article.get("use_cases_b64", "")).strip()
    ascii_diagram = b64_to_str(article.get("ascii_diagram_b64", "")).rstrip()
    approaches = article.get("approaches", [])
    complexity = b64_to_str(article.get("complexity_b64", "")).strip()

    md = f"# {title}\n\n"

    md += "## 1. Introduction\n"
    md += f"{intro}\n\n"

    md += "## 2. When is it used?\n"
    md += f"{use_cases}\n\n"

    md += "## 3. ASCII Diagram\n\n"
    md += f"```\n{ascii_diagram}\n```\n\n"

    md += "## 4. Approaches\n\n"

    for app in approaches:
        name = b64_to_str(app.get("name_b64", "")).strip()
        explanation = b64_to_str(app.get("explanation_b64", "")).strip()
        cpp_code = b64_to_str(app.get("cpp_b64", "")).rstrip()
        java_code = b64_to_str(app.get("java_b64", "")).rstrip()
        py_code = b64_to_str(app.get("python_b64", "")).rstrip()

        if not name:
            continue

        md += f"### {name}\n\n"
        md += f"{explanation}\n\n"
        md += "#### Code Implementations\n\n"

        # C++
        md += "<details>\n"
        md += "<summary><strong>C++</strong></summary>\n\n"
        md += "```cpp\n"
        md += f"{cpp_code}\n"
        md += "```\n\n"
        md += "</details>\n\n"

        # Java
        md += "<details>\n"
        md += "<summary><strong>Java</strong></summary>\n\n"
        md += "```java\n"
        md += f"{java_code}\n"
        md += "```\n\n"
        md += "</details>\n\n"

        # Python
        md += "<details>\n"
        md += "<summary><strong>Python</strong></summary>\n\n"
        md += "```python\n"
        md += f"{py_code}\n"
        md += "```\n\n"
        md += "</details>\n\n"

        md += "---\n\n"

    md += "## 5. Time & Space Complexity\n\n"
    md += f"{complexity}\n"

    return md


# -------------------------------------------------------------
# README Auto-Updater
# -------------------------------------------------------------
def update_readme():
    DAILY_DIR.mkdir(exist_ok=True)
    readme = ROOT / "README.md"

    lines = []
    lines.append("# Data Structures & Algorithms – Auto-Generated Encyclopedia\n")
    lines.append(
        "This repository is automatically updated daily with new DSA articles "
        "generated using Google's Gemini API.\n"
    )
    lines.append("## Daily Index\n")

    if not DAILY_DIR.exists():
        readme.write_text("\n".join(lines), encoding="utf-8")
        return

    for day_dir in sorted(DAILY_DIR.glob("day_*")):
        if not day_dir.is_dir():
            continue
        day_name = day_dir.name  # day_001
        lines.append(f"### {day_name.replace('_', ' ').title()}\n")
        for md_file in sorted(day_dir.glob("*.md")):
            rel_path = md_file.relative_to(ROOT).as_posix()
            title = md_file.stem.replace("_", " ").title()
            lines.append(f"- [{title}]({rel_path})")
        lines.append("")

    readme.write_text("\n".join(lines), encoding="utf-8")


# -------------------------------------------------------------
# Main Process
# -------------------------------------------------------------
def main():
    DAILY_DIR.mkdir(exist_ok=True)
    GEN_DIR.mkdir(exist_ok=True)

    state = load_state()
    used_slugs = state.get("used_slugs", [])

    prompt = build_prompt(used_slugs)
    articles = call_gemini(prompt)

    day_index = state.get("day", 1)
    day_dir = DAILY_DIR / f"day_{day_index:03d}"
    day_dir.mkdir(parents=True, exist_ok=True)

    new_slugs = []

    for article in articles:
        raw_title = b64_to_str(article.get("title_b64", "")).strip() or "topic"
        slug = slugify(raw_title)
        base_slug = slug
        i = 1
        while slug in used_slugs or (day_dir / f"{slug}.md").exists():
            slug = f"{base_slug}_{i}"
            i += 1

        md_path = day_dir / f"{slug}.md"
        md_content = render_markdown(article)
        md_path.write_text(md_content, encoding="utf-8")

        new_slugs.append(slug)

    state["day"] = day_index + 1
    state["used_slugs"] = used_slugs + new_slugs
    save_state(state)

    update_readme()


# -------------------------------------------------------------
# Entry Point
# -------------------------------------------------------------
if __name__ == "__main__":
    main()