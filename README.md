<div align="center">

# ✈️ Flight to Rescue: Aviation Emergency & Rescue Mission 🚁
### *Interactive Multi-Scene 2D Computer Graphics Simulation & Animation System*

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-2D_Graphics-5586A4?style=for-the-badge&logo=opengl&logoColor=white)
![GLUT](https://img.shields.io/badge/FreeGLUT-Windowing_&_Events-2C2D72?style=for-the-badge&logo=opengl&logoColor=white)
![Win32 Audio](https://img.shields.io/badge/WinMM_API-Async_WAV_Audio-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Status](https://img.shields.io/badge/Project_Status-Completed-success?style=for-the-badge)

**Course:** Computer Graphics (Section: I — Final Group Project)  
**Semester:** Spring 2025–2026 | **Institution:** American International University-Bangladesh (AIUB)  
**Supervisor:** Mahfujur Rahman | **Domain:** 🖥️ 2D Computer Graphics / ✈️ Aviation Emergency & Maritime Simulation

</div>

---

## 📖 Table of Contents
- [📌 Project Overview](#-project-overview)
- [🎯 Simulation Storyline & Objectives](#-simulation-storyline--objectives)
- [🛠️ Tech Stack & Libraries Used](#️-tech-stack--libraries-used)
- [🏗️ System Architecture & Scene Pipeline](#️-system-architecture--scene-pipeline)
- [✨ Core Features & Scene Breakdown](#-core-features--scene-breakdown)
- [📸 Project Screenshots & Visual Walkthrough](#-project-screenshots--visual-walkthrough)
- [🎮 Interactive Controls Guide](#-interactive-controls-guide)
- [🧱 Program Structure & Computer Graphics Concepts](#-program-structure--computer-graphics-concepts)
- [🚀 Installation & Setup Guide](#-installation--setup-guide)
- [👥 Project Group Members](#-project-group-members)

---

## 📌 Project Overview
**Flight to Rescue: An Aviation Emergency Scenario & Rescue Mission** is a story-driven, multi-scene 2D graphical simulation built entirely from scratch in **C++** using **OpenGL (`GL/gl.h`)** and the **OpenGL Utility Toolkit (`GL/glut.h`)**.

Developed without any external game engines or pre-made sprite sheets, every visual asset in the simulation—including commercial aircraft, multi-gate airport terminals, urban skylines, runway perspectives, clouds, animated ocean waves, rescue boats, and flocks of birds—is mathematically constructed using OpenGL vertex primitives, polygons, and trigonometric circle-generation algorithms. The system runs on a unified **50 FPS (`20ms`) animation timer** and integrates asynchronous `.wav` sound effects via the Windows Multimedia API (`PlaySound`).

---

## 🎯 Simulation Storyline & Objectives
The simulation walks the user through a complete 5-stage aviation narrative, demonstrating real-time user control and geometric transformations at every stage:
* **🛫 Pre-Flight & Airport Operations:** Showcases a bustling airport terminal with parked aircraft, ground service vehicles, moving clouds, and a foreground jet taxiing for departure.
* **✈️ Runway Acceleration & Take-Off:** Models pitch-up rotational dynamics (`glRotatef`) and translational climb (`glTranslatef`) as the aircraft leaves the runway.
* **☁️ High-Altitude Cruising & Emergency Descent:** Uses multi-layered parallax scrolling during mid-air flight before transitioning into an emergency water ditching scenario with collision deceleration.
* **🚤 Maritime Search & Rescue Operation:** Depicts the post-landing rescue mission featuring day/night environment switching, blinking aircraft distress beacons, and interactive rescue vessels.

---

## 🛠️ Tech Stack & Libraries Used

| Category | Technology / Library | Purpose in Project |
| :--- | :--- | :--- |
| **Programming Language** | 💻 **C++ (`cmath`, `cstdio`, `cstring`)** | Core simulation state logic, trigonometric math calculations, and callback management |
| **Core Graphics API** | 🎨 **OpenGL (`GL/gl.h`)** | 2D primitive rendering (`GL_POLYGON`, `GL_TRIANGLE_FAN`, `GL_QUADS`, `GL_LINES`), matrix transformations, and alpha blending |
| **Windowing & Event Toolkit** | 🖼️ **GLUT / FreeGLUT (`GL/glut.h`)** | Double-buffered window management, `glutTimerFunc` 50 FPS loop, bitmap text rendering, and keyboard/mouse hooks |
| **Audio Integration** | 🔊 **Win32 Multimedia API (`windows.h` / `winmm`)** | Asynchronous background `.wav` sound playback and scene-specific audio switching via `PlaySound()` |
| **Development Environment** | 🛠️ **Code::Blocks / Visual Studio (MinGW)** | C++ compilation, OpenGL/GLUT library linking, and debugging |
| **Version Control** | 🔗 **Git & GitHub** | Source code management, project documentation, and portfolio hosting |

---

## 🏗️ System Architecture & Scene Pipeline

* **Projection Coordinate Space:** 2D Orthographic Projection (`gluOrtho2D(-400, 400, -300, 300)`)
* **Window Resolution:** `800 x 600` Pixels (`GLUT_DOUBLE | GLUT_RGB`)
* **Master Frame Rate:** `50 FPS` (`glutTimerFunc(20, update, 0)`)
* **Global State Controller:** `currentPage` (`0` to `6`) routing rendering, timer updates, keyboard/mouse inputs, and audio streams

```text
+-------------------------------------------------------------------------+
|                        MAIN GLUT EVENT LOOP (50 FPS)                    |
|        glutDisplayFunc(display)  |  glutTimerFunc(20, update, 0)        |
+----------------------------------+--------------------------------------+
                                   |
       +---------------------------+---------------------------+
       |                           |                           |
       v                           v                           v
+--------------+           +---------------+           +---------------+
| Input Router |           | State Manager |           | Audio Manager |
| Keyboard &   |---------->| (currentPage) |---------->| Win32 Async   |
| Mouse Hooks  |           | Pages: 0 to 6 |           | WAV Playback  |
+--------------+           +-------+-------+           +---------------+
                                   |
     +------------+------------+---+--------+------------+------------+
     |            |            |            |            |            |
     v            v            v            v            v            v
 [Page 0-1]   [Page 2]     [Page 3]     [Page 4]     [Page 5]     [Page 6]
 Cover & UI   Airport      Runway       Mid-Air      Emergency    Maritime
 Overlay      Terminal     Take-Off     Cruising     Water Crash  Rescue Op
```

<details>
<summary><b>🔍 Click to Expand: Scene State Mapping & Audio Files</b></summary>
<br>

| Page Index (`currentPage`) | Scene Title | Primary Render Function | Associated Audio File (`.wav`) |
| :---: | :--- | :--- | :--- |
| **`0`** | Front Cover Page | `sh_displayCoverPage()` | `planesoundeffect.wav` |
| **`1`** | Interactive Instructions UI | `sh_displayInstructionPage()` | `planesoundeffect.wav` |
| **`2`** | Scene 1: Airport Terminal & Taxiing | `sh_displayAirportScene()` | `planesoundeffect.wav` |
| **`3`** | Scene 2: Runway Take-Off | `niha_display()` | `airport_sound.wav` |
| **`4`** | Scene 3: Mid-Air Plane Cruising | `ann_display()` | `plane1.wav` |
| **`5`** | Scene 4: Emergency Water Ditching | `displaySoykot()` | `airplane-fly-by-02.wav` |
| **`6`** | Scene 5: Maritime Rescue Operation | `hasib_display()` | `Rescue.wav` |

</details>

---

## ✨ Core Features & Scene Breakdown

1. **🖥️ Alpha-Blended Front Cover & Instructions Overlay (Pages 0 & 1):**
   - Renders a live, animated airport background dimmed with a translucent dark overlay using OpenGL alpha blending (`GL_SRC_ALPHA`, `GL_ONE_MINUS_SRC_ALPHA`).
   - Displays structured academic metadata, group member details, and scene-by-scene control instructions using `GLUT_BITMAP_HELVETICA_18` and `GLUT_BITMAP_HELVETICA_12`.

2. **🏢 Scene 1 — Airport Terminal & Runway Taxiing (Page 2):**
   - Features a multi-building city skyline, 6-gate glass terminal, control poles, runway markings, ground service cones/vehicles, 3 parked aircraft, drifting clouds, and bird flocks.
   - Right-clicking triggers the foreground commercial airplane to taxi and accelerate across the runway.

3. **🛫 Scene 2 — Dynamic Aircraft Take-Off (Page 3):**
   - Models diagonal runway perspective, air traffic control tower, terminal buildings, and golden sun lighting.
   - Applies simultaneous X/Y translation and gradual pitch-up angle rotation (`niha_planeAngle` up to `15.0°`) alongside sine-wave bird wing flapping (`sin(niha_wingFlap)`).

4. **☁️ Scene 3 — High-Altitude Parallax Cruising (Page 4):**
   - Implements multi-speed parallax background scrolling (`0.4x` cloud velocity and `0.8x` bird velocity relative to `ann_backgroundX`) to create depth perception during flight.
   - Allows real-time speed modulation and instant pause/resume toggles.

5. **🌊 Scene 4 — Aviation Emergency & Water Ditching (Page 5):**
   - Simulates an emergency descent over a sunset ocean horizon with sailboats and seabirds.
   - Features two-stage water impact physics: upon hitting `waterLine = -50.0f`, the aircraft rapidly decelerates (`0.3f`) before coming to a complete halt at `-58.0f` and cutting engine sound.

6. **🚁 Scene 5 — Maritime Rescue Operation & Day/Night Cycle (Page 6):**
   - Depicts the partially submerged aircraft tilted at `15°` in the ocean surrounded by mountains, animated waves, and 4 rescue boats.
   - Includes a real-time **Day/Night Mode toggle (`n`)** that switches the sky gradient, transforms the sun into a moon, hides daytime birds, and activates a blinking red distress beacon on the aircraft tail.

---

## 📸 Project Screenshots & Visual Walkthrough


### 📋 Front Cover & Instructions UI

| Front Cover Page (`Page 0`) | Project Instructions (`Page 1`) |
| :---: | :---: |
| ![Cover Page](assets/cover_page.png) | ![Instructions Page](assets/instructions_page.png) |

### 🎬 Simulation Storyboard (Scenes 1 – 5)

| Scene 1: Airport Terminal & Runway (`Page 2`) | Scene 2: Aircraft Take-Off (`Page 3`) |
| :---: | :---: |
| ![Scene 1 Airport](assets/scene1_airport.png) | ![Scene 2 Takeoff](assets/scene2_takeoff.png) |

| Scene 3: Mid-Air Cruising (`Page 4`) | Scene 4: Emergency Water Ditching (`Page 5`) |
| :---: | :---: |
| ![Scene 3 Cruising](assets/scene3_flying.png) | ![Scene 4 Crash](assets/scene4_crash.png) |

| Scene 5: Maritime Rescue — Day Mode (`Page 6`) | Scene 5: Maritime Rescue — Night Mode (`Page 6`) |
| :---: | :---: |
| ![Scene 5 Rescue Day](assets/scene5_rescue_day.png) | ![Scene 5 Rescue Night](assets/scene5_rescue_night.png) |

---

## 🎮 Interactive Controls Guide

| Scene / Scope | Key / Mouse Input | Action / Functionality |
| :--- | :---: | :--- |
| **🌐 Global Navigation** | `Right Arrow` / `Enter` | Advance to the next display scene (`currentPage++`) |
| **🌐 Global Navigation** | `Left Arrow` / `Backspace` | Return to the previous display scene (`currentPage--`) |
| **🏢 Scene 1: Airport** | `Right Mouse Click` | Start foreground airplane taxiing & takeoff |
| **🏢 Scene 1: Airport** | `s` / `u` / `m` | Play (`s`/`u`) or Mute (`m`) airport sound effects |
| **🛫 Scene 2: Take-Off** | `w` / `s` or `Up` / `Down` | Adjust airplane vertical altitude (`niha_planeY`) |
| **🛫 Scene 2: Take-Off** | `f` / `d` | Increase (`f`) or Decrease (`d`) takeoff speed multiplier |
| **🛫 Scene 2: Take-Off** | `Left` / `Right Click` | Pitch aircraft Up (`Left`) or Down (`Right`) |
| **🛫 Scene 2: Take-Off** | `m` / `u` | Mute (`m`) or Unmute (`u`) takeoff audio |
| **☁️ Scene 3: Cruising** | `p` or `Left Click` | Pause / Resume flight & parallax animation |
| **☁️ Scene 3: Cruising** | `Up` / `Down Arrow` | Increase / Decrease cruising speed (`ann_speed`) |
| **☁️ Scene 3: Cruising** | `m` / `u` | Mute (`m`) or Unmute (`u`) flight audio |
| **🌊 Scene 4: Crash** | `s` / `u` | Trigger emergency descent animation & fly-by audio |
| **🌊 Scene 4: Crash** | `Left Mouse Click` | Pause emergency descent simulation |
| **🌊 Scene 4: Crash** | `Up` / `Down Arrow` | Increase / Decrease descent, bird, and boat speeds |
| **🌊 Scene 4: Crash** | `m` | Mute crash scene audio |
| **🚁 Scene 5: Rescue** | `n` | Toggle between **Day Mode** and **Night Mode** |
| **🚁 Scene 5: Rescue** | `Up` / `Down Arrow` | Start (`Up`) or Stop (`Down`) rescue boat navigation |
| **🚁 Scene 5: Rescue** | `Right Mouse Click` | Reverse rescue boat movement direction |
| **🚁 Scene 5: Rescue** | `m` / `u` | Mute (`m`) or Unmute (`u`) rescue siren audio |

---

## 🧱 Program Structure & Computer Graphics Concepts

<details>
<summary><b>🧩 Click to Expand: OpenGL Rendering Techniques & Repository Structure</b></summary>
<br>

* **Hierarchical Matrix Transformations (`glPushMatrix` / `glPopMatrix`):**
  * Isolates object-specific translations (`glTranslatef`) and rotations (`glRotatef`) so moving clouds, flapping birds, and pitching aircraft do not distort the static background coordinates.
* **Trigonometric Procedural Geometry:**
  * Circles, suns, moons, aircraft noses, and wheels are generated dynamically using `GL_TRIANGLE_FAN` and `GL_POLYGON` loops over $2\pi$ radians (`cos(theta)`, `sin(theta)`).
  * Bird wing flapping and rescue boat pathing use continuous sine and absolute value functions (`sin()`, `fabs()`).
* **Alpha Blending & Raster Typography:**
  * Uses `glEnable(GL_BLEND)` with `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)` for semi-transparent UI panels and `glutBitmapCharacter()` for text rendering.

### 📂 Repository File Structure
```text
Flight-to-Rescue-OpenGL-Simulation/
├── assets/                          # Project screenshots for README showcase
│   ├── cover_page.png
│   ├── instructions_page.png
│   ├── scene1_airport.png
│   ├── scene2_takeoff.png
│   ├── scene3_flying.png
│   ├── scene4_crash.png
│   ├── scene5_rescue_day.png
│   └── scene5_rescue_night.png
├── audio/                           # WAV sound files (place alongside .exe when running)
│   ├── planesoundeffect.wav
│   ├── airport_sound.wav
│   ├── plane1.wav
│   ├── airplane-fly-by-02.wav
│   └── Rescue.wav
├── Final Project Graphics.cpp       # Complete C++ OpenGL/GLUT source code
└── README.md                        # Project Documentation
```

</details>

---

## 🚀 Installation & Setup Guide

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/<your-username>/Flight-to-Rescue-OpenGL-Simulation.git
cd Flight-to-Rescue-OpenGL-Simulation
```

### 2️⃣ Configure OpenGL / FreeGLUT & Audio Files
Ensure you are on **Windows** with MinGW (`g++`) and `freeglut` installed, and make sure the `.wav` audio files are in the same working directory as the compiled executable.

### 3️⃣ Compile & Run the Project
* **Option A — Using Terminal (MinGW `g++`):**
```bash
g++ "Final Project Graphics.cpp" -o FlightToRescue.exe -lfreeglut -lopengl32 -lglu32 -lwinmm
./FlightToRescue.exe
```
* **Option B — Using Code::Blocks IDE:**
  1. Open Code::Blocks and create a new **GLUT/OpenGL Project**.
  2. Replace `main.cpp` with `Final Project Graphics.cpp`.
  3. Navigate to **Project ➔ Build Options ➔ Linker Settings** and add `winmm` alongside `glut32` (or `freeglut`), `opengl32`, and `glu32`.
  4. Press **F9 (Build and Run)**.

---

## 👥 Project Group Members

| Name | Student ID | Role & Scene Contribution |
| :--- | :---: | :--- |
| **Shahadat Hossain** | `23-51341-1` | **Cover Page, Instructions UI & Scene 1:** Airport Terminal, Urban Skyline, Ground Vehicles & Runway Taxiing |
| **Niha Karmokar** | `24-56028-1` | **Scene 2:** Runway Perspective, Control Tower, Sine-Wave Bird Flapping & Aircraft Take-Off Physics |
| **Zahin Tahiat Annesha** | `23-50414-1` | **Scene 3:** High-Altitude Cruising & Multi-Layer Parallax Cloud/Bird Animation |
| **Mir Moahtasim Billah Soykot** | `23-50414-1` | **Scene 4 & System Integration:** Emergency Water Ditching Simulation & Master Multi-Scene Code Merging |
| **Hamidul Islam** | `23-50447-1` | **Scene 5:** Maritime Rescue Operation, Day/Night Environment Toggle, Distress Beacon & Boat Mechanics |

---

<div align="center">
  <i>Developed for Computer Graphics (Section I) — Spring 2025–2026 Semester at AIUB.</i>
</div>
