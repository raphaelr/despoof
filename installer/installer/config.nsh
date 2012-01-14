!ifndef VERSION
	!define /file VERSION ..\..\version.txt
!endif

!ifndef TARGET_DIR
	!define TARGET_DIR "."
!endif

!ifndef TARGET_PATH
	!define TARGET_PATH "${TARGET_DIR}\despoof-${VERSION}-setup.exe"
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

!define UNINSTALL_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\Despoof"
