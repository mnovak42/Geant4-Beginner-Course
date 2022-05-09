M. Novak December 2019
-----------------------

This is the intermediate state of our application. It contains only the mandatory
interface implementations, i.e. only those that are essential for a Geant4 simulaiton
application. Therefore, we are able to execute our simulation but:

 - we do not see much about what happens during the simulation since we do not collect
   any infomation (we will implement some optional user actions to collect some data)

 - there is no any flexibity of the application, i.e. target material, thickness, are
   hard coded so we need to change them in the code and rebuild the application (we
   will add some UI commands for these such that these can be configured from a
   standard Geant4 macro file)

There are two versions of the main function provided:

 - one without any visualisation or user interface(UI): therefore it can be used only in
   batch mode

 - one including user interface(UI) and visualisation settings

The second will be used to show some of the very minimal visualization and UI related
possibilities. Both graphical(GUI) and terminal like(e.g. tcsh) UI option will be tried
including and not visualisation from them.
