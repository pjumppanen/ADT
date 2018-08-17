createUUID <- function()
{
  # example "41919986-9594-11e6-bcd9-8fb587d839a2"
  # not strictly universally unique but it is good enough for what it gets
  # used for.
  rnums <- as.integer(256 * runif(16))
  UUID  <- sprintf("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                   rnums[1],
                   rnums[2],
                   rnums[3],
                   rnums[4],
                   rnums[5],
                   rnums[6],
                   rnums[7],
                   rnums[8],
                   rnums[9],
                   rnums[10],
                   rnums[11],
                   rnums[12],
                   rnums[13],
                   rnums[14],
                   rnums[15],
                   rnums[16])

  return (UUID)
}

new.adt <- function(path, name, short.name, target=NA, language="cpp", src.templates=NA, overwrite=FALSE)
{
  not.dir <- !file.info(path)$isdir

  if (is.na(not.dir) || not.dir)
  {
    stop("path ", path, " does not exist")
  }

  OS        <- .Platform$OS.type
  IsWindows <- OS == "windows"

  if (is.na(target))
  {
    # Guess target based on platform running
    if (IsWindows)
    {
      target <- "vs"
    }
    else
    {
      target <- "autoconf"
    }
  }

  if (language != "cpp")
  {
    stop(paste("language", language, "not supported"))
  }

  if (IsWindows)
  {
    # find path to ADT as we need it to obtain the project file templates
    adt.path <- dirname(dirname(Sys.which('adt.exe'))) # drop the /bin/adt.exe

    if (!nzchar( adt.path))
    {
      stop("cannot find ADT. Looks like it is not installed")
    }
  }
  else
  {
    adt.path  <- "/usr/local/share/adt"

    # check for presence of adt
    if (!file.exists(adt.path))
    {
      stop("cannot find adt template files. make and install adt")
    }
  }

  if (is.na(src.templates))
  {
    src.templates.path <- paste(adt.path, "/templates/source", sep="")
  }
  else
  {
    src.templates.path <- src.templates
  }

  if (target == "vs")
  {
    # Visual Studio Project
    solution.path <- paste(gsub("\\\\","/", path), "/", name, sep="")
    project.path  <- paste(solution.path, "/", name, sep="")
    adt.path.win  <- gsub("/","\\\\", adt.path)

    # create guids
    solution.guid <- createUUID()
    project.guid  <- createUUID()

    if (dir.exists(solution.path))
    {
      if (!overwrite)
      {
        stop("Solution folder already exists! Use overwrite argument to force the result.")
      }
    }
    else
    {
      # create solution folder
      dir.create(solution.path)
    }

    Sys.chmod(solution.path, mode="0777")

    if (!dir.exists(project.path))
    {
      # create project folder
      dir.create(project.path)
    }

    Sys.chmod(project.path, mode="0777")

    # create project file
    project.template <- paste(adt.path, "/templates/make/VisualStudio/base.vcxproj", sep="")
    solution.folder  <- paste(path, "/", name, sep="")
    project.folder   <- paste(solution.folder, "/", name, sep="")
    project.name     <- paste(project.folder, "/", name, ".vcxproj", sep="")

    con           <- file(project.template, "rt")
    template.text <- readLines(con)
    close(con)

    template.text <- gsub("$(filename)", name, template.text, fixed=TRUE)
    template.text <- gsub("$(project-guid)", project.guid, template.text, fixed=TRUE)
    template.text <- gsub("$(adt-path)", adt.path.win, template.text, fixed=TRUE)

    con <- file(project.name, "wb")
    writeLines(template.text, con)
    close(con)

    Sys.chmod(project.name, mode="0755")

    # create source files
    source.templates <- c("base.hpp", "base.cpp", "Rbase.hpp", "Rbase.cpp", "base_registration.cpp", "base.mk")

    for (cn in 1:length(source.templates))
    {
      source.template <- paste(src.templates.path, "/cpp/", source.templates[cn], sep="")
      source.filename <- gsub("base", name, source.templates[cn], fixed=TRUE)

      con           <- file(source.template, "rt")
      template.text <- readLines(con)
      close(con)

      template.text <- gsub("$(classname)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(short-classname)", short.name, template.text, fixed=TRUE)
      template.text <- gsub("$(libname)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(filename)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(title-comment)", paste("//", source.filename), template.text, fixed=TRUE)

      source.name <- paste(project.folder, "/", source.filename, sep="")

      con <- file(source.name, "wb")
      writeLines(template.text, con)
      close(con)

      Sys.chmod(source.name, mode="0755")
    }

    # create solution file
    solution.template <- paste(adt.path, "/templates/make/VisualStudio/base.sln", sep="")
    solution.name     <- paste(solution.folder, "/", name, ".sln", sep="")

    con           <- file(solution.template, "rt")
    template.text <- readLines(con)
    close(con)

    template.text <- gsub("$(libname)", name, template.text, fixed=TRUE)
    template.text <- gsub("$(project-guid)", project.guid, template.text, fixed=TRUE)
    template.text <- gsub("$(solution-guid)", solution.guid, template.text, fixed=TRUE)

    con <- file(solution.name, "wb")
    writeLines(template.text, con)
    close(con)

    Sys.chmod(solution.name, mode="0755")
  }
  else if (target == "autoconf")
  {
    # autoconf project
    project.path  <- paste(path, "/", name, sep="")
    src.path      <- paste(project.path, "/src", sep="")

    if (dir.exists(project.path))
    {
      if (!overwrite)
      {
        stop("Project folder already exists! Use overwrite argument to force the result.")
      }
    }
    else
    {
      # create project folder
      dir.create(project.path)
      Sys.chmod(project.path, mode="0777")
    }

    # create src folder
    dir.create(src.path)
    Sys.chmod(src.path, mode="0777")

    # create source files
    source.templates <- c("base.hpp", "base.cpp", "Rbase.hpp", "Rbase.cpp", "base_registration.cpp", "base.mk", "run_mk")

    for (cn in 1:length(source.templates))
    {
      source.template <- paste(src.templates.path, "/cpp/", source.templates[cn], sep="")
      source.filename <- gsub("base", name, source.templates[cn], fixed=TRUE)

      con           <- file(source.template, "rt")
      template.text <- readLines(con)
      close(con)

      template.text <- gsub("$(classname)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(short-classname)", short.name, template.text, fixed=TRUE)
      template.text <- gsub("$(libname)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(filename)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(title-comment)", paste("//", source.filename), template.text, fixed=TRUE)

      source.name <- paste(src.path, "/", source.filename, sep="")

      con <- file(source.name, "wb")
      writeLines(template.text, con)
      close(con)

      Sys.chmod(source.name, mode="0755")
    }

    # create autoconf files
    ac.templates <- c("configure.ac", "Makefile.am", "init_config.sh", "COPYING", "INSTALL", "README", "ChangeLog")

    for (cn in 1:length(ac.templates))
    {
      ac.template <- paste(adt.path, "/templates/make/autoconf/", ac.templates[cn], sep="")
      ac.filename <- ac.templates[cn]

      con           <- file(ac.template, "rt")
      template.text <- readLines(con)
      close(con)

      template.text <- gsub("$(short-classname)", short.name, template.text, fixed=TRUE)
      template.text <- gsub("$(libname)", name, template.text, fixed=TRUE)
      template.text <- gsub("$(filename)", name, template.text, fixed=TRUE)

      ac.name <- paste(project.path, "/", ac.filename, sep="")

      con <- file(ac.name, "wb")
      writeLines(template.text, con)
      close(con)

      Sys.chmod(ac.name, mode="0755")
    }
  }
  else
  {
    stop("target ", target," not supported")
  }
}
