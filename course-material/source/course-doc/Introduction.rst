
.. _ref-Introduction:

Introduction
--------------

What is :guilabel:`Geant4`?
....................................

:guilabel:`Geant4` is an open source **toolkit** for developing applications that simulates the passage of particles through matter. It is very important to understand the difference between being a **toolkit** or a concrete simulation application with a main **program**. :guilabel:`Geant4` as a **toolkit** *provides* all the necessary *components* that are needed *to* **describe** *and to* **solve** *particle transport* simulation *problems*.

A concrete simulation problem, with its own unique *geometrical, material configurations*, *physics* modelling *setting* etc., can be **described** by using these components eventually *leading to a given simulation application with a* **main program**. After the description of a unique simulation problem is given, :guilabel:`Geant4` as a **toolkit** also provides the solution of the underlying particle transport modelling problem. The **Monte Carlo method** is utilised by :guilabel:`Geant4` to **solve** the related transport equations taking into account the geometrical, physics, etc. constraints provided by the **toolkit** based description of the application. This eventually leads to a *setp-by-step* computation of the particle transport through the given geometry (hence the name GEometry ANd Traking), where each of the step is limited by either a geometry (e.g. volume boundary) or a physics (e.g. bremsstrahlung photon emission of an :math:`e^-`) related constraint. Several interaction points are provided for the users during this solution process for collecting and propagating information over a wide range of granularity: from the smallest, i.e. individual step level up to a complete run.

It is important to recognise, that *different* particle transport modelling *problems* require *different descriptions* (e.g. different geometry, physics configuration, etc.) *while the solution* of the transport problem itself as well as the possible user interaction points *are generic*, i.e. independent from the details of the concrete problem. This is achieved by :guilabel:`Geant4` through providing carefully designed **interfaces** both for the **description** of the simulation problem as well as for the user interactions (e.g. for the detector geometry description). These interfaces decouples or **abstracts** away the concrete implementation of the related components (e.g. the concrete detector geometry) from the solution algorithm while ensures that the required functionalities and information are supplied.


Our goal in the next few days
.......................................

:guilabel:`Geant4` **toolkit developers** work directory on the toolkit continuously extending and improving its modelling, description, etc. functionalities. :guilabel:`Geant4` **application developers** work on developing simulation applications by describing a well defined particle transport simulation problem and configuration making use of the available functionalities of the toolkit. These simulation applications can then be utilised by any **users** to obtain the results of the related simulation problem, usually with some possible further configuration options made available by the application developer (e.g. primary particle type and/or energy). The **toolkit developers** also provides example application that very often demonstrate a particular functionality of the toolkit. These example applications are also provided by toolkit.

Our goal is to make the very first steps in the next few days on the way to become a :guilabel:`Geant4` **application developer**. In order to do so, you will become familiar with the most important building blocks provided by the :guilabel:`Geant4` **toolkit** to describe any particle transport simulation problem. These definitely include the so-called **mandatory** as well as some of the **optional components**. While the **mandatory components**, such as the detector description, physics configuration, primary generator are essentially needed to define a particular simulation problem, the **optional** components provide the possibility to collect all the required information during the solution of the simulation problem.


Format
.....................................

As mentioned above, :guilabel:`Geant4` application development requires the implementation of (at least the mandatory) C++ interfaces provided by the toolkit to define the particular simulation problem. As in most cases of programming, implementing example applications, with steadily increasing complexity while acquiring the theoretical background information required by the next step, provides an efficient way to reach a confident level of experience. This tutorial was designed along this experience as well. Therefore, we will implement a concrete particle transport simulation problem together from scratch in a step-by-step way. Each implementation step will be preceded by a detailed explanation of the required related theoretical background. A relatively simple simulation problem was selected in order to keep focusing on a generic :guilabel:`Geant4` application structure with a clear understanding of the role of the most important components and their relations instead of diving deep in one particular direction. In spite of it simplicity, our target application problem represents very well the structure of a generic :guilabel:`Geant4` application. Therefore, the format and content of the tutorial provide the opportunity for acquiring rather confident basic :guilabel:`Geant4` application developer skills.

During this process, we will heavily rely on information supplied by the :guilabel:`Geant4` :g4userdoc:`UsersGuides/ForApplicationDeveloper/html/index.html, Book For Application Developers` completed by the source code inspection of the related interfaces and other toolkit component implementations.


.. admonition:: **Take-home**
   :class: takehome

   :guilabel:`Geant4` is a **toolkit** which means that provides the building blocks to describe your particle transport problems, then the generic solution of the transport problem using the Monet Carlo method. Toolkit developers extends the description, modelling, etc. functionalities of the toolkit while application developers provides final simulation applications based on the toolkit that can be utilised by the users.


.. tip::

   The example applications, provided by the **toolkit developers** as part of the toolkit itself, serve as a good starting point for developing your own application. Try to find the closest to your needs, use it as a starting point and modify, extend according to your own modelling problem.


.. admonition:: **What's next?**
   :class: whatsnext

   Before starting to implement our target simulation problem, the next section ensures that we are all on the same (or at least similar) page regarding some technical details: understanding of some key C++ object oriented concepts such as *interfaces*, becoming familiar with our local :guilabel:`Geant4` implementation and `CMake` build system, etc.






Bals lashd

Let's cite something from the application doxygen documentation here e.g. the
first the section of the final application description (not doxygen)
:ref:`final application <ref-final-application-description>` then now the
doxygen documentation of the detector construction
:cpp:class:`YourDetectorConstruction`



Here I use a link to a Geant4 file that is on GitHub
:g4file:`source/particles/leptons/include/G4Electron.hh` then I use a G4 class name
:g4cname:`G4ClassNames`

:file:`file names: ../fname`

:envvar:`environment variables: G4INSTALL`

:g4cname:`G4ClassNames`

:guilabel:`Geant4`


.. code-block:: cpp

   #include "G4Something.hh"

   int main() {

     std::cout << " Someting " << std::endl;
     return 0;
   }




.. just drow a horizontal line as separator at the end of each section
.. raw:: latex

   \par\noindent\rule{\textwidth}{0.5pt}
