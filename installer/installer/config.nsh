!ifndef TARGET_PATH
	!define TARGET_PATH "despoof-setup.exe"
!endif

!ifndef SOURCE_DIR
	!ifndef CONFIGURATION
		!define CONFIGURATION "RelWithDebInfo"
	!endif
	!ifndef BUILD_DIR
		!define BUILD_DIR "build"
	!endif
	!define SOURCE_DIR "..\..\${BUILD_DIR}\${CONFIGURATION}"
!endif

!ifndef VERSION
	!define /file VERSION ..\..\version.txt
!endif

!define UNINSTALL_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\Despoof"
