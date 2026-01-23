# cc-context-watch Implementation Plan

A step-by-step guide to building a context usage indicator for Claude Code in Rust.

---

## Phase 1: Research & Understanding

Before writing code, you need to understand how to interface with Claude Code.

### 1.1 Understand Claude Code's Extension Points

Claude Code offers several integration mechanisms:

- **Hooks**: Shell commands that run in response to events (tool calls, notifications, etc.)
- **MCP (Model Context Protocol)**: Servers that extend Claude Code's capabilities
- **Status line**: A customizable display area in the Claude Code UI

**Tasks:**
- [ ] Read Claude Code documentation on hooks: run `/hooks` in Claude Code
- [ ] Explore MCP server setup: check `~/.claude/` for config files
- [ ] Investigate if there's an API or event that exposes context usage

### 1.2 Find Context Usage Data

You need to discover how/where context usage is exposed.

**Tasks:**
- [ ] Check if Claude Code emits context info in hook events
- [ ] Look for any CLI flags or commands that show context stats
- [ ] Investigate the Claude API response format for usage metadata

---

## Phase 2: Architecture Design

### 2.1 Choose Integration Method

Based on your research, decide how your tool will:
1. **Receive** context usage data (hook event? polling? API response parsing?)
2. **Display** the progress bar (terminal UI? status line integration?)

### 2.2 Design Data Flow

```
[Claude Code] --> [Your Tool] --> [Display]
     |                |               |
     |                |               +-- Progress bar rendering
     |                +-- Parse context usage %
     +-- Emit usage data (hook/event/API)
```

---

## Phase 3: Rust Project Setup

### 3.1 Initialize Project

**Tasks:**
- [ ] Run `cargo init` to create a new Rust project
- [ ] Set up basic project structure:
  ```
  cc-context-watch/
  ├── src/
  │   └── main.rs
  ├── Cargo.toml
  └── README.md
  ```

### 3.2 Dependencies to Consider

- JSON parsing (for API/event data): `serde` and `serde_json`
- Terminal UI (if needed): `crossterm` or `ratatui`
- Async runtime (if needed): `tokio`

---

## Phase 4: Core Implementation

### 4.1 Input Handling

**Tasks:**
- [ ] Implement reading context data from your chosen source
- [ ] Parse the usage percentage from the data

### 4.2 Progress Bar Rendering

**Tasks:**
- [ ] Create a function to render a progress bar given a percentage
- [ ] Example output: `Context: [████████░░░░░░░░] 52%`

### 4.3 Integration with Claude Code

**Tasks:**
- [ ] Wire up your tool to receive data from Claude Code
- [ ] Test the end-to-end flow

---

## Phase 5: Polish & Testing

- [ ] Handle edge cases (0%, 100%, invalid data)
- [ ] Add error handling for missing/malformed input
- [ ] Test with real Claude Code sessions
- [ ] Update README with installation/usage instructions

---

## Resources

- Claude Code docs: `/help` command within Claude Code
- MCP specification: https://modelcontextprotocol.io/
- Rust serde library: https://serde.rs/
- Rust crossterm library: https://github.com/crossterm-rs/crossterm

---

## Notes

_Use this section to jot down findings as you work through the plan._
