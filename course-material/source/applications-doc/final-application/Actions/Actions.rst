.. _ref-Actions-doc:

Code documentation of the user action part of the application
-----------------------------------------------------------------------

This section contains the code documentation of all the user actions of the application developed during the course.


The **mandatory** interface implementations
.................................................

This is the **mandatory** action initialization (that includes the construction and registration of the primary generator action).
An object form the action initialization implementation class must be registered in the run manager inside the main (e.g. :cpp:func:`main` in :ref:`yourMainApplication <ref-yourMainApplication-file>`)
of each application.

.. doxygenclass:: YourActionInitialization
   :project: Geant4 Beginner Course
   :members:
   :private-members:


.. doxygenclass:: YourPrimaryGeneratorAction
   :project: Geant4 Beginner Course
   :members:
   :private-members:



Some of the **optional** interface implementations
....................................................


.. doxygenclass:: YourRun
   :project: Geant4 Beginner Course
   :members:
   :private-members:


.. doxygenclass:: YourRunAction
   :project: Geant4 Beginner Course
   :members:
   :private-members:

.. doxygenclass:: YourEventAction
   :project: Geant4 Beginner Course
   :members:
   :private-members:

.. doxygenclass:: YourSteppingAction
   :project: Geant4 Beginner Course
   :members:
   :private-members:
