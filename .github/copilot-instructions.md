# Copilot instructions for nf-Community-Targets

## Repository purpose

This repository is not a general application codebase. It is a catalog of community-maintained firmware targets for .NET nanoFramework. The root contains board metadata, build presets, and CI wiring; each board lives in its own folder under `ChibiOS/` or `TI_SimpleLink/`.

Typical target layout:

- `README.md`: board description and usage notes
- `CMakePresets.json`: board-specific CMake preset used by the build pipeline
- `managed_helpers/`: optional C# helper code for that target
- platform-specific folders such as `ChibiOS/...` or `TI_SimpleLink/...`

The build system is centered on the external `nanoframework/nf-interpreter` repo and the Azure Pipelines templates in `azure-pipelines-templates/`.

## Build, test, and validation commands

There is no repository-local unit test suite or linter in this repo. Validation is performed by the CMake presets and by the Azure Pipelines jobs in `azure-pipelines.yml`.

Useful commands from the repo root:

- List available presets:
  `cmake --list-presets`
- Configure a single target preset (example):
  `cmake --preset ST_NUCLEO64_F401RE_NF`
- Build a single target preset (example):
  `cmake --build --preset ST_NUCLEO64_F401RE_NF`
- Open a specific target folder and inspect its preset/README before changing it:
  `cd ChibiOS/ST_NUCLEO64_F401RE_NF`

CI behavior is driven by `azure-pipelines.yml` and the templates under `azure-pipelines-templates/`. A PR or commit can trigger building only selected targets using tags like:

- `[x] ST_NUCLEO64_F401RE_NF`
- `[x] BUILD ALL`

For a single-target validation workflow, prefer the matching board preset and build command above rather than trying to run the entire repository build.

## High-level architecture

The repo is organized around three main concerns:

1. Target catalogs
   - `ChibiOS/`: STM32-based community targets
   - `TI_SimpleLink/`: TI CC13xx/CC26xx launchpad targets
   - Each target folder is self-contained and usually includes a README and a board preset

2. Build orchestration
   - Root `CMakePresets.json` includes all board presets
   - Azure pipeline jobs download/install toolchains and then build images against the external `nf-interpreter` repo
   - Multiple templates handle STM32, TI SimpleLink, and ESP32 builds

3. Publishing and release metadata
   - Readme files describe board features, pin mapping, and managed helpers
   - CI publishes artifacts for the selected target to the package feed; this is the main release mechanism

This repo does not contain the core nanoFramework runtime; it packages target definitions and board-specific metadata that are consumed by the interpreter and build toolchain.

## Key conventions

- Preserve the existing board directory naming pattern: uppercase target names with platform-specific folders and consistent README structure.
- When editing a board target, check its local `README.md` and `CMakePresets.json` first; those are the key source-of-truth files for that board.
- The root `CMakePresets.json` is a registry of included board presets; keep it aligned when adding or renaming a target.
- PRs follow `.github/PULL_REQUEST_TEMPLATE.md`. Target-specific checks are expected to indicate which board(s) are affected.
- Documentation is user-facing and board-specific; keep README updates consistent with pin mappings and supported peripherals.
- In this repo, the build and release flow is CI-driven rather than local app/test-driven, so changes should be validated in the smallest relevant preset or board-specific pipeline path.

## AI-specific notes

- Favor surgical edits in the affected target folder rather than broad repository-wide changes.
- When a change impacts a target or its docs, update the corresponding board README and preset together.
- If a new target is added, also update the root preset registry and the README target list where relevant.
