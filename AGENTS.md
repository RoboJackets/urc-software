# URC Software Agent Guide

This file defines the engineering standards for changes to this repository.

## Repository Context

- This is a ROS 2 Humble workspace targeting Ubuntu 22.04.
- First-party packages use C++17, Python launch files, `ament_cmake`, and `colcon`.
- The repository root is `rover_ws/src`; run `colcon` commands from `rover_ws`.
- Treat `external/` as vendored submodule code. Do not modify it unless the task
  explicitly requires a dependency change.
- Do not edit generated files or files under `build/`, `install/`, or `log/`.
- Inspect `git status` before editing and preserve unrelated user changes.

## Working Principles

- Understand the owning package before changing it. Read its `CMakeLists.txt`,
  `package.xml`, configuration, public headers, and nearby implementation.
- Make the smallest coherent change that fully solves the requested problem.
- Apply these standards strongly to new and meaningfully modified code.
- When legacy code near the change violates these standards, improve the changed
  responsibility and nearby correctness hazards without starting an unrelated
  repository-wide refactor.
- Keep dependencies, install rules, launch files, configuration, interfaces, and
  documentation synchronized with behavior.

## Architecture and File Organization

- Keep ROS nodes thin. They should primarily own parameters, publishers,
  subscriptions, services, actions, timers, lifecycle behavior, and top-level
  orchestration.
- Move algorithms, state machines, validation, transformations, filtering,
  scoring, serialization, and hardware-independent policy into focused
  components.
- Main orchestration functions should read as a short sequence of clearly named
  operations.
- Prefer one principal responsibility per file and one abstraction level per
  function.
- Split substantial responsibilities into domain-named header/source pairs.
  Avoid using generic `helpers`, `utils`, or `common` files as dumping grounds.
- Public headers contain contracts, declarations, public types, and only the
  members necessary to represent the type. Implementations and file-local
  helpers belong in `.cpp` files.
- Use anonymous namespaces for helpers used by only one translation unit.
- Use the conventional package structure:
  - `include/<package>/` for public headers
  - `src/` for implementations and private components
  - `config/` for runtime configuration
  - `launch/` for launch composition
  - ROS-specific asset folders such as `urdf/`, `rviz/`, `world/`, and `meshes/`
    only for their respective assets
- Treat roughly 250 non-generated source lines per file and 40 lines per function
  as decomposition review triggers. Exceeding them requires a cohesive reason.
- Split by responsibility rather than line count. Do not replace one monolith
  with many trivial or tightly coupled files.

## Clean Code

- Use descriptive, domain-specific names. Code structure and naming should make
  normal control flow understandable without explanatory comments.
- Give each function one clear purpose with explicit inputs and outputs.
- Prefer early returns and shallow control flow over deep nesting.
- Avoid hidden side effects, boolean control parameters, oversized parameter
  lists, duplicated logic, mutable global state, and ambiguous ownership.
- Use RAII, initialized state, const-correctness, narrow interfaces, standard
  library facilities, and explicit ownership.
- Use smart pointers only when pointer semantics are required. Never use a raw
  pointer to express ownership.
- Include only what a file uses. Keep public headers dependency-light and use
  package-scoped include paths.
- Replace unexplained literals with well-named constants or validated parameters
  when the value has domain meaning.
- Do not use non-standard umbrella headers such as `bits/stdc++.h`.
- Remove unused includes, members, locals, functions, and unreachable code.
- Do not leave commented-out code, debugging statements, or unjustified warning
  suppressions.
- Do not swallow exceptions broadly. Handle errors at the layer that can add
  context or make a safe recovery decision.
- Follow `ament_code_style.cfg` for C++ formatting and `ament_flake8` for Python.

## Comments and Documentation

- Keep package documentation concise and task-oriented. Cover the package's
  purpose, primary usage, public contracts, operational constraints, and links
  to deeper references.
- Do not duplicate source structure, enumerate incidental launch options, or
  document test-only and niche workflows unless they are operationally
  important. Let code, configuration, and `ros2 launch --show-args` provide
  exhaustive details.
- Comments are exceptional. Prefer clearer names, smaller functions, and better
  structure.
- Add a comment only when it explains information the code cannot express well:
  - design intent or a non-obvious invariant
  - a safety or failure constraint
  - frames, units, coordinate conventions, ownership, or concurrency contracts
  - non-obvious mathematics, algorithms, or source references
  - a deliberate performance tradeoff or platform constraint
- Do not narrate statements, label obvious sections, explain straightforward
  loops, repeat symbol names, or preserve debugging notes.
- Remove stale or redundant comments when modifying the associated code.
- Document public behavior and contracts rather than implementation trivia.
- TODOs must identify a concrete remaining problem, not a vague improvement.

## Runtime and Complexity

- Be mindful of runtime and memory complexity when choosing algorithms and data
  structures. Formal Big-O documentation is not required.
- Avoid quadratic work or repeated full-data scans when a practical linear or
  logarithmic approach exists.
- Keep callbacks, timers, control loops, and hardware paths bounded and
  non-blocking.
- Avoid unnecessary ROS message copies, heap allocations, filesystem access,
  network waits, transform waits, and verbose logging in hot paths.
- Move expensive work out of latency-sensitive callbacks when needed. Define
  synchronization, cancellation, ownership, and stale-result behavior clearly.
- Prefer incremental updates, bounded queues, timeouts, and configurable work
  limits for inputs that can grow indefinitely.
- Cache expensive derived data only when ownership and invalidation are clear.
- Prefer observed behavior and profiling over speculative micro-optimization.

## ROS and Robotics Standards

- Parameterize operational topics, services, actions, frames, device paths,
  thresholds, limits, and rates. Validate parameters during initialization.
- Internal values that are not operationally tunable may be local `constexpr`
  constants.
- Put normal parameter overrides in package YAML. Keep launch files focused on
  composition, configuration loading, and high-level mode selection.
- Choose QoS deliberately for the data's reliability, durability, and frequency.
- Preserve timestamps, frame ownership, coordinate conventions, and physical
  units across interfaces.
- Use an appropriate executor model, mutex, or atomic strategy for shared callback
  state. Avoid holding locks while publishing, logging, or performing slow work.
- Handle invalid input, stale data, unavailable services, missing transforms,
  cancellation, partial initialization, and shutdown safely.
- Throttle repetitive diagnostics. Logging must not dominate sensor or control
  callbacks.
- Prefer simulation when it can validate the behavior safely. Use physical
  hardware only when the task and available environment authorize it.
- Never silently change safety limits, hardware assumptions, network addresses,
  device paths, topic contracts, frames, or units.

## Validation and Completion

- Build affected packages and run applicable repository lint checks when the
  environment supports them.
- Validate behavior in simulation or on hardware as appropriate. Qualitative
  validation is acceptable for normal robotics behavior; use quantitative
  evaluation when the task specifically requires measurable performance.
- New unit tests and launch tests are not required unless explicitly requested.
- Run `git diff --check` before completion.
- Report what changed, what was checked, what was observed, and anything that
  could not be verified.
- Never claim that a build, lint check, simulation, hardware trial, or performance
  target passed unless it was actually run and observed.
