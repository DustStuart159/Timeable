# Timeable
- project with C language
- comprise of creatTimeable and observeTimeable main functions
- comprise of SupportFunctions are getCurrentTime and pretreatLocalDir
- project funtions are linked by extern variables and functions

  # creatTimeable
  - creatTimeable for Day, Week, Month, Quater and Year
  - return TimeableFile
  - compose of addTasks
  
  # addTasks
  - assign number of Tasks that you need to do
  - write Tasks on File
  - comprise addTaskArray
  
  # addTaskArray
  - creatTimeable in SpeacialStructure
  - comprise of arrangeTasks
  
  # arrangeTaskArray
  - arrange CreatedTaskArray
  
  # observeTimeable
  - show Timeable that you requested
  - compose of getRequestFile and showTimeable
  
    # getRequestFile
    - show folders and files that you can access
    - return Path of File is sRF
    - comprise of showControllerMenu
    
    # showConrollerMenu
    - display SelectionScreen
    - get Char from Keyboard
    - return File or Folder Name
  
  # showTimeable
  - get sRF
  - showTimeable
  
# getCurrentTime
- getRealTime
- return SpecialString include information of RealTime

# pretreatLocalDir
- creatDataFolder include Files of Timeable
- return DataFolderPath
