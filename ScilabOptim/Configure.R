ConfFile  <-file("Makeconf")
Lines     <- c(paste0('R_SHARE_DIR=', R.home("share")), paste0('R_HOME=', R.home()))
writeLines(Lines, ConfFile)
close(ConfFile)
