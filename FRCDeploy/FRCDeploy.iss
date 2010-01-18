; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{55BFAD25-4C79-4365-9271-A18FEF6516E1}
AppName=WebDMA
AppVerName=WebDMA 0.2
AppPublisher=Dustin Spicuzza
AppPublisherURL=http://code.google.com/p/webdma/
AppSupportURL=http://code.google.com/p/webdma/
AppUpdatesURL=http://code.google.com/p/webdma/
DefaultDirName={pf}\WebDMA
DefaultGroupName=WebDMA
LicenseFile=C:\Documents and Settings\dspicuzz\My Documents\webdma\LICENSE
InfoAfterFile=C:\Documents and Settings\dspicuzz\My Documents\webdma\README.FRC
OutputBaseFilename=WebDMAInstaller
Compression=lzma
SolidCompression=yes


[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
; FTP Source installation
Source: "FRCDeploy.exe"; DestDir: "{app}"; Flags: ignoreversion

; WebDMA object file installation
Source: "..\src\PPC603gnu\WebDMA\Debug\WebDMA.out"; DestDir: "{app}"; Flags: ignoreversion

; WWW files installation
Source: "..\www\*"; DestDir: "{app}\www"; Flags: ignoreversion createallsubdirs recursesubdirs 

; Header files installation
Source: "..\include\WebDMA\WebDMA.h"; DestDir: "C:\WindRiver\vxworks-6.3\target\h\WebDMA"; Flags: ignoreversion
Source: "..\include\WebDMA\VariableProxy.h"; DestDir: "C:\WindRiver\vxworks-6.3\target\h\WebDMA"; Flags: ignoreversion
Source: "..\include\WebDMA\VariableProxyFlags.h"; DestDir: "C:\WindRiver\vxworks-6.3\target\h\WebDMA"; Flags: ignoreversion


[Icons]
Name: "{group}\WebDMA"; Filename: "{app}\FRCDeploy.exe"

[Run]
Filename: "{app}\FRCDeploy.exe"; Description: "{cm:LaunchProgram,WebDMA}"; Flags: nowait postinstall skipifsilent




