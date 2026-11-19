# SpyGame

SpyGame is an Unreal Engine 5 C++ vertical slice for an original, James-Bond-inspired spy thriller. It includes a generated tech-demo compound, third-person controls, four-stage mission logic, and a complete mission narrative.

## Mission

**Operation Glass Crown**

An old enemy is converting Meridian Station's power core into a covert targeting system. Agent Vale must:

1. Enter the service wing.
2. Recover the Glass Crown cipher.
3. Disable the signal jammer.
4. Reach the extraction helipad.

The mission and dialogue are data-oriented structures in `USpyMissionDataAsset`, with the default story supplied by `USpyMissionSubsystem`.

## Requirements

- Unreal Engine 5.3 or later
- A C++ toolchain supported by Unreal (Visual Studio 2022 on Windows or Xcode/Clang on macOS)

The project intentionally uses only Unreal's built-in cube mesh and C++-generated geometry, so no external art marketplace assets are required.

## Open and play

1. Generate project files using your Unreal installation.
2. Open `SpyGame.uproject`.
3. Open the editor and press **Play**.
4. Use **W/A/S/D** to move and enter each glowing objective marker.

`ASpyGameGameMode` generates the compound and mission markers at startup.

## Build

From a Visual Studio Developer Command Prompt:

```text
UnrealBuildTool.exe SpyGameEditor Win64 Development
```

The exact engine tool paths vary by installation. You can also build with `Tools/GenerateProjectFiles` (or **Generate Visual Studio project files**) followed by the Unreal editor.

## Tests

Open **Unreal Editor > Tools > Test Automation** and run:

```text
SpyGame.Mission.DefaultStoryIsComplete
```