; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of example1.nsi
; there. 

;--------------------------------

; The name of the installer
Name "SumCoin Setup"
Caption "SumCoin cryptocurrency coin setup"

; The file to write
OutFile "sumcoin-setup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\SumCoin

; Request application privileges for Windows Vista
RequestExecutionLevel admin

Icon "sumcoin.ico"
BrandingText "(c) 2015 SumCoin Developers"

SetDatablockOptimize on

;--------------------------------

; Pages

Page license
LicenseData "sumcoin-license.rtf"

Page directory
Page instfiles

!define MUI_FINISHPAGE_RUN "$INSTDIR\sumcoin-qt.exe"

UninstPage uninstConfirm
UninstPage instfiles


;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File ..\release\sumcoin-qt.exe
  File libwinpthread-1.dll
  
  ; write uninstall strings
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SumCoin" "DisplayName" "SumCoin (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SumCoin" "UninstallString" '"$INSTDIR\cc-uninst.exe"'
  WriteUninstaller "cc-uninst.exe"
  
  CreateShortcut "$DESKTOP\SumCoin.lnk" "$INSTDIR\sumcoin-qt.exe"
  
SectionEnd ; end the section

Function .onInstSuccess
  ExecShell open "$DESKTOP\SumCoin.lnk"
FunctionEnd


;--------------------------------

; Uninstaller

UninstallText "This will uninstall SumCoin. Hit next to continue."
UninstallIcon "sumcoin.ico"

Section "Uninstall"

  Delete "$DESKTOP\SumCoin.lnk"
  Delete "$INSTDIR\sumcoin-qt.exe"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\cc-uninst.exe"
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SumCoin"
SectionEnd
