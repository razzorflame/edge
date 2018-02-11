# Dependencies directory
---
This directory is used for storing dependencies, such as SFML library.
In fact, you can store them wherever you want, as long as valid directory is set for specified macros inside Visual Studio project properties.
## How EDGE makes use of dependencies?
---
EDGE is based on SFML and OpenGL, thus it needs to be supplied with working and compatible version of the libraries.
EDGE project uses user-defined environment macros to specify *include* and *lib* folders for each dependency.
The following list contains information about required dependencies, supported versions and macros used to locate them:
|Dependency              |Supported version   |Macro     |Remarks                                        |
|------------------------|:------------------:|----------|-----------------------------------------------|
|SFML                    |2.4.2               |SFMLDir   |Generally every version >= than 2.0 should work|
## Where can I configure dependency macros?

