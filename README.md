# Combinatorial Mesh Calculus (CMC)

## About
This repository contains software implementation (written in C and built with
GNU Make) and mathematical notes (written in LaTeX) related to the research done
by me, Kiprian Berbatov, at the University of Manchester.
My research is focused on the development of calculus on discrete
microstructures, represented by combinatorial meshes, and using it for
formulating discrete and intrinsic physical models on solids.
The lead of the research group that I am part of is Prof Andrey Jivkov.

The project is hosted on GitHub at <https://github.com/kipiberbatov/cmc>.
A website for the project is produced via Github Actions, and is hosted on
GitHub Pages at <https://kipiberbatov.github.io/cmc>.

## Introduction to Combinatorial Mesh Calculus
**Combinatorial meshes** are discrete structures that can be realised as
subdivisions of continuum (smooth) manifolds.
**Combinatorial mesh calculus** (**CMC**) is a calculus on those structures
which only uses the intrinsic information (cell connectivity and cell measures)
but not the continuum embedding.
It is an approach similar to **Discrete Exterior Calculus** (**DEC**) and was
initially called **Intrinsic Discrete Exterior Calculus** (**IDEC**),
emphasising its intrinsic, combinatorial nature.
However, the calculus we develop is not an extension of DEC but works on
different kinds of meshes, and so we prefer a new term, CMC.
Indeed, in DEC the typical domain is a simplicial mesh, but in CMC the spatial
domain is a mesh of (combinatorial) simple polytopes and the main objects of
interests are the so called **combinatorial differential forms**.
Those discrete forms are mapped to cochains on a special subdivision, which we
call the **Forman subdivision**, which results in a mesh of topological cubes,
which we call **quasi-cubes**.
For this reason we introduce the new term, Combinatorial Mesh Calculus.

CMC's founding article, "Diffusion in multi-dimensional solids using Forman’s
combinatorial differential forms" can be found as a preprint at
<https://arxiv.org/abs/2201.03704> or as published article at
<https://doi.org/10.1016/j.apm.2022.05.043>.
In this article we introduced combinatorial differential forms on a mesh
$\mathcal{M}$, and its Forman subdivision $\mathcal{K}$.
On $\mathcal{K}$ we introduced a **discrete metric tensor** from which a
**discrete inner product** was derived.
The discrete inner product was used to canonically construct **discrete Hodge
star**, **adjoint coboundary**, and **discrete Laplace** operators.
The main benefit of using combinatorial differential forms for physical models
of solids is the ability to formulate interactions between adjacent cells of
different dimensions, directly on the solid's microstructure, represented by
the original cell structure $\mathcal{M}$.
A model resembling strong differential formulation for diffusion zero Neumann
boundary conditions was formulated and tested.
The code for the tests was written in Matlab by Dr Pieter Boom, available at
<https://github.com/boompiet/Forman_MATLAB>.

In my PhD thesis, "Discrete approaches to mechanics and physics of solids"
<https://pure.manchester.ac.uk/ws/portalfiles/portal/261212897/FULL_TEXT.PDF>,
I proposed a direct definition of the discrete inner product, without
introducing a discrete metric tensor, and showed its optimal behaviour on
grids of orthogonal parallelotopes.
This renewed definition has been used ever since.

Further applications of CMC for fluid flows on porous media on rock samples were
performed in the article
"Combinatorial differential forms for multi-dimensional fluid flow in porous
media: A unified framework for volumetric pores, fractures, and channels",
published at
<https://www.sciencedirect.com/science/article/pii/S030917082500209X>.
The calculations were done by Changhao Liu, expanding on Pieter's code.
Changhao's code is available at <https://github.com/changhaoliu-UOM/flow_2024>.

Our most recent article, "Variational formulations of transport on combinatorial
meshes", is available as a preprint at <https://arxiv.org/abs/2505.09443>,
and is under revision for publication in a scientific journal.
There we describe transport phenomena in continuous media in terms of smooth
differential forms, and in discrete media in terms of combinatorial differential
forms (cochains in the Forman subdivision), both with mixed boundary conditions.
From the resulting formulations, we derive variational formulations (primal and
mixed), both on smooth manifolds and on meshes.
Selected examples of discrete problems resembling continuous ones with exact
solutions are presented.
This repository contains the code for those examples, which are a selected
subset of the steady state examples available in the codebase.
Examples of transient problems are not shown in the article, but they are
available in the codebase.
All calculated 2D examples are visualised at
<https://kipiberbatov.github.io/cmc/main.pdf>.
3D examples are currently not visualised.

## Project state
The API is highly unstable and I regularly change a lot of functionality all at
once.
There are many things to be improved: naming conventions, data structures,
replacing/removing old functionality, improving the building process, etc.

## Modules
- array: functions working on integers and floating point numbers and
arrays structures of those types;
importantly the **jagged1**, ..., **jagged4** structures of jagged integer
arrays (of levels 1-4) are implemented;
- algebra: using the structure **cs** from
[CSparse library](https://github.com/DrTimothyAldenDavis/SuiteSparse/tree/stable/CSparse)
as a backend, a wrapper structure **matrix\_sparse** is created;
a simpler structure **vector\_sparse** is also created;
- region: structures **simplex** and **quasi\_cube**
and functions operating on them are implemented;
- mesh: structure **mesh** and functions on meshes are implemented;
the structure **mesh\_qc** is the same as **mesh** but is intended to be used
for quasi-cubical meshes resulting from applying **forman**;
- diffusion: includes various structures for encoding the input data for
diffusion problems (in particular, heat equation), as well as implementations
of solution methods for those problems;
- graphics: structures and functions for drawing images and animations on a
canvas in a backend-independent way (the canvas and animation backend are
selected at runtime according to the command line arguments);

## Plugins
- diffusion: problem data and exact solutions to transient and steady-state
continuous diffusion problems;
- canvas: procedures for drawing shapes on a canvas, currently with Cairo;
- animation: procedures for producing animations based on the canvas data;
PDF, SVG and GTK animation backends are supported via the Cairo canvas backend.

## Dependencies

You need the following programs and installed on your system in order to clone,
build the project and run the text-outputting demos:
- git
- C compiler (GCC or Clang)
- GNU make

In order to build the canvas and animation plugins, run PDF- and SVG-outputting
demos and GTK animations, you need the following software
- pkg-config
- Cairo
- GTK+ 3

To build the documentation, you need the LaTeX compiler **pdflatex**. 

On MacOS git, Clang and GNU make should be shipped with
[command line tools for XCode](https://developer.apple.com/xcode/resources/).
As a better alternative, you can install [Homebrew](https://brew.sh), and run

```
brew install git
brew install llvm
brew install make
```

(Clang is a part of LLVM).
The remaining dependencies are installed in the same manner:

```
brew install pkg-config
brew install cairo
brew install gtk+3
brew install texlive
```

For Linux you can install the required dependencies using your preferred
package manager or [Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux).
(Cairo and GTK+ may already be installed by your distribution.)

For Windows, you should install
[Windows subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install),
[Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux),
and the required dependencies.


## Building on Unix-like platforms

Make sure you have all the dependencies installed.
Via the command line vavigate to your preferred location on your computer.
Type the following:

```
git clone https://github.com/kipiberbatov/cmc
cd cmc
make -j
```

(`make -j` will speed the build process by executing in parallel)
After running `make -j` the result is a directory **build/release**
(if you want a debug build, type `make -j MODE=debug CFLAGS='-g -O0'`).
Inside **build/release** (substitute **release** with **debug** in debug mode)
the following directories are created:
- **build/release/obj** where source files from [code/c/src](/code/c/src)
are compiled into object files;
- **build/release/lib** where object files from **build/release/obj**
are archived;
- **build/release/bin** where source files from [code/c/main](/code/c/main)
are compiled and linked against libraries in **build/release/lib**;
- **build/release/txt** where text-outputting demos are run using
executables from **build/release/bin**,
manually written input data from [data](/data), and already generated files from
**build/release/txt**.

You can generate PDFs of various images and animations (e.g., meshes, cochains)
in a freshly created directory **build/release/pdf** by typing
```
make -j pdf
```
PDF documents are produced by Cairo and represent animations such that
each page is a snapshot of that animation at a given moment of time.
Some of the PDFs have thousands of pages
and will take (uncompressed) tens of megabytes of disk space.
Note that although compilation, linking and running text-outputting demos are
extremely fast (in milliseconds on average for every file),
generating PDFs may take from a few seconds to a minute for the big animations.

Similarly, you can generate SVGs of various images in a freshly created
directory **build/release/svg** by typing
```
make -j svg
```
Unfortunately, SVG animations, although being generated, cannot be read by most
browsers as they use the unsupported pageSet element for multiple pages.
(One SVG animation of window with changing colors is generated as an example.)

You can run GTK animations in pop-up windows by typing
```
make gtk
```
(Log files documenting animation runs will be saved in a freshly created
directory **build/release/gtk**.)
Note that GTK+ windows will appear and they have to be manually closed after
you are finished watching them.
If you want to close them automatically after finishing, type
```
make CLOSE_AUTOMATICALLY=1 gtk
```

You can build the LaTeX documentation in a freshly created **build/docs**
directory by typing
```
make docs
```

You can combine the documentation with web assets to create a static website by
typing
```
make website
```
This will create a **build/website** directory with all the web assets.
In fact this is the way the website
<https://kipiberbatov.github.io/cmc>
is deployed as is evident by the file
[.github/workflows/github-pages.yaml](/.github/workflows/github-pages.yaml).

You can clean the generated files (the build directory) using
```
make distclean
```

There are various smaller cleans that will delete certain types of files.
For instance `make clean` will clean the object files.
You can look the files in [code/make](/code/make) to see all the cleaning
options (they end with **_clean** or **_distclean**).

## Building for Windows

### Cross-compiling Windows x86_64 binaries on Unix

At the moment I am working on porting the project to Windows.
There are two main issues related to that:
1. Dynamic loading uses Unix API by `dlfcn.h`.
   This will be fixed by constructing an abstract API and choosing Unix/Windows
   API depending on the ontext.
2. Makefiles use Unix path separators and GCC/Clang compiler options.
   This is currently overcome by using MinGW.

At the moment all internal source files can be compiled by using MinGW.
Consequently, all demonstrations in modules `{array,algebra,region,mesh}` can
be run by Wine.
In order to allow this, a Makefile macro `INTERPRETER` is introduced
(empty by default).
On native runs it is not used, but on cross-platform runs (Windows over Unix)
it needs to be set, e.g., `INTERPRETER=wine`.
Hence, MinGW and Wine need to be installed.
With Homebrew this is achieved by running
```bash
brew install mingw-w64
brew innstall --cask wine-stable
```
(Note that `wine-stable` is built for the x86_64 architecture.
Hence, it nrequires Rosetta 2 in order to run on Apple silicon.)
The full build process is summarised in the Bash script `mingw.sh` that executes
the cross-platform build (Windows over Unix) by running
```bash
bash ./mingw.sh
```
