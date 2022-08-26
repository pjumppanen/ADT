WinSub       <- ""
StaticLibExt <- "a"
Arch         <- ""
WinTarget    <- "" 

if (Sys.info()["sysname"] == "Windows")
{
  StaticLibExt <- "lib"

  if (Sys.info()["machine"]=="x86-64")
  {
    WinSub    <- "x64"
    WinTarget <- WinSub
  }
  else
  {
    WinSub    <- "i386"
    WinTarget <- "Win32"
  }
}

Lines <- readLines(paste0(R.home(), "/etc/", WinSub, "/Makeconf"))

for (Line in Lines)
{
  # look for R_ARCH=/???
  if (length(grep("^\\s*R_ARCH\\s*=\\s*/", Line, perl = TRUE)) > 0)
  {
    Arch <- gsub("^\\s*R_ARCH\\s*=\\s*/", "", Line, perl = TRUE)
  }
}

ConfFile <-file("Makeconf")
Lines    <- c(paste0('R_SHARE_DIR=', R.home("share")), 
              paste0('R_HOME=', R.home()),
              paste0('ARCH=', Arch),
              paste0('STATICLIB_EXT=', StaticLibExt))

writeLines(Lines, ConfFile)
close(ConfFile)

if (nchar(WinSub) > 0)
{
  InstallBatchFile <- file("install.bat")
  Lines            <- c(paste0('SET bat_path=%~dp0'),
                        paste0('copy /Y %bat_path%\\lib\\', WinSub, '\\ScilabOptim.dll %bat_path%\\..\\objs\\', WinTarget, '\\Debug'),
                        paste0('copy /Y %bat_path%\\lib\\', WinSub, '\\ScilabOptim.dll %bat_path%\\..\\objs\\', WinTarget, '\\Release'))

  writeLines(Lines, InstallBatchFile)

  close(InstallBatchFile)
}
