!include config.nsh
!include functions.nsh

!include FileFunc.nsh
!include Sections.nsh

SetCompressor /solid lzma
OutFile "${TARGET_PATH}"
Name "Despoof"
RequestExecutionLevel admin
InstallDir "$PROGRAMFILES\Despoof"
LicenseData "..\..\COPYING.rtf"
ShowInstDetails show
ShowUninstDetails show

VIAddVersionKey "ProductName" "Despoof"
VIAddVersionKey "ProductVersion" "${VERSION}"
VIAddVersionKey "FileDescription" "Installer for Despoof"
VIAddVersionKey "FileVersion" "${VERSION}"
VIAddVersionKey "CompanyName" "tape software"
VIAddVersionKey "LegalCopyright" "(c) 2012 Raphael Robatsch"
VIProductVersion ${VERSION}

Page license
Page directory
Page components
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "Despoof" section_main
	SectionIn RO
	
	SetOutPath $INSTDIR
	!insertmacro DsFile "despoof.exe"
	!insertmacro DsFile "despoof-svc.exe"
	!insertmacro DsFile "despoof-svctool.exe"
	!insertmacro DsFile "log-console.dll"
	!insertmacro DsFile "log-file.dll"
	!insertmacro DsFile "nw-pcap.dll"
	
	!insertmacro DsFinalizeFiles
	WriteUninstaller "uninstall.exe"
	WriteRegStr HKLM ${UNINSTALL_KEY} "DisplayName" "Despoof"
	WriteRegStr HKLM ${UNINSTALL_KEY} "Publisher" "tape software"
	WriteRegStr HKLM ${UNINSTALL_KEY} "DisplayVersion" "${VERSION}"
	WriteRegStr HKLM ${UNINSTALL_KEY} "UninstallString" '"$INSTDIR\uninstall.exe"'
	WriteRegStr HKLM ${UNINSTALL_KEY} "QuietUninstallString" '"$INSTDIR\uninstall.exe" /S'
	WriteRegStr HKLM ${UNINSTALL_KEY} "InstallLocation" "$INSTDIR"
	WriteRegDWORD HKLM ${UNINSTALL_KEY} "NoModify" 1
	WriteRegDWORD HKLM ${UNINSTALL_KEY} "NoRepair" 1
	
	SectionGetSize ${section_main} $0
	WriteRegDWORD HKLM ${UNINSTALL_KEY} "EstimatedSize" "$0"
SectionEnd

Section "Start Despoof with Windows" section_service
	ExecWait '"$INSTDIR\despoof-svctool" --install --start'
	WriteRegDWORD HKLM ${UNINSTALL_KEY} "DespoofServiceInstalled" 1
SectionEnd

Section "Uninstall"
	ReadRegDWORD $0 HKLM ${UNINSTALL_KEY} "DespoofServiceInstalled"
	IntCmp $0 0 skip_service_uninstall
	ExecWait '"$INSTDIR\despoof-svctool" --stop --uninstall'
skip_service_uninstall:
	!insertmacro DsDeleteFiles
	Delete "$INSTDIR\uninstall.exe"
	RMDir "$INSTDIR"
	DeleteRegKey HKLM ${UNINSTALL_KEY}
SectionEnd

Function .onInit
	${GetParameters} $0
	${GetOptions} $0 "noservice" $1
	IfErrors noselect_service
	!insertmacro UnselectSection ${section_service}
	noselect_service:
FunctionEnd
