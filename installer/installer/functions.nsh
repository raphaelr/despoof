!include StrFunc.nsh

Var files
Var filecount

!macro DsFile filename
	File /oname=${filename} "${SOURCE_DIR}\${filename}"
	StrCpy $files "$files:${filename}"
	IntOp $filecount $filecount + 1
!macroend

!macro DsFinalizeFiles
	WriteRegStr HKLM ${UNINSTALL_KEY} "DespoofFileList" "$files"
	WriteRegDWORD HKLM ${UNINSTALL_KEY} "DespoofFileCount" $filecount
!macroend

${UnStrTok}
!macro DsDeleteFiles
	ReadRegStr $files HKLM ${UNINSTALL_KEY} "DespoofFileList"
	ReadRegDWORD $filecount HKLM ${UNINSTALL_KEY} "DespoofFileCount"
	IntOp $filecount $filecount - 1
dsd_iter:
	${UnStrTok} $0 $files ":" $filecount "1"
	Delete "$INSTDIR\$0"
	IntOp $filecount $filecount - 1
	IntCmp $filecount -1 dsd_out dsd_out dsd_iter
dsd_out:
!macroend
