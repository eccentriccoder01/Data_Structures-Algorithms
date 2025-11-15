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

For each topic, return the following JSON structure:

{
  "title": "",
  "intro": "",
  "use_cases": "",
  "ascii_diagram": "",
  "approaches": [
    {
      "name": "",
      "explanation": "",
      "cpp": "",
      "java": "",
      "python": ""
    }
  ],
  "complexity": ""
}

IMPORTANT:
- Output only a JSON array of {NUM_ARTICLES_PER_DAY} objects.
- No markdown, no backticks, no explanation.
    """.strip()


# -------------------------------------------------------------
# Gemini API Call
# -------------------------------------------------------------
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

    data = json.loads(text)

    if not isinstance(data, list):
        raise ValueError("Gemini response is not a JSON array")

    if len(data) != NUM_ARTICLES_PER_DAY:
        raise ValueError(
            f"Expected {NUM_ARTICLES_PER_DAY} articles, got {len(data)}"
        )

    return data


# -------------------------------------------------------------
# Markdown Renderer
# -------------------------------------------------------------
def render_markdown(article: dict) -> str:
    title = article["title"].strip()
    intro = article["intro"].strip()
    use_cases = article["use_cases"].strip()
    ascii_diagram = article["ascii_diagram"].rstrip()
    approaches = article["approaches"]
    complexity = article["complexity"].strip()

    md = f"# {title}\n\n"

    md += "## 1. Introduction\n"
    md += f"{intro}\n\n"

    md += "## 2. When is it used?\n"
    md += f"{use_cases}\n\n"

    md += "## 3. ASCII Diagram\n\n"
    md += f"```\n{ascii_diagram}\n```\n\n"

    md += "## 4. Approaches\n\n"

    for app in approaches:
        name = app["name"].strip()
        explanation = app["explanation"].strip()
        cpp_code = app["cpp"].rstrip()
        java_code = app["java"].rstrip()
        py_code = app["python"].rstrip()

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
        raw_title = article["title"]
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
