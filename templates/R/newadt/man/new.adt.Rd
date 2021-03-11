\name{new.adt}

\alias{new.adt}


\title{Skeleton ADT Project Creation}
\description{
Setting up an ADT project from scratch can be a complex task. This package
makes creating a skeleton package a breeze. Once set up it is generally a straight
forward process adding the code needed to solve a particular problem.
}

\usage{
new.adt(path, name, short.name, target=NA, language="cpp", src.templates=NA, overwrite=FALSE)
}

\arguments{
  \item{path}{path to the folder in which to create the project}
  \item{name}{name to give to the project. Only use characters that are allowable for naming objects, typical all the letters and numbers plus the underscore character.}
  \item{short.name}{a contraction or nick name for the project used for file an function prefixes. This should be short with the same character restrictions as above.}
  \item{target}{string specifying the target build enviroment. Can be \code{vs} (Visual Studio IDE), \code{libtools}, \code{xcode} (Xcode IDE), \code{autoconf} (gnu autoconf / automake) or \code{lazarus} (Lazarus Pascal IDE)}
  \item{language}{string specifying the language to target. Can be \code{cpp} or \code{pascal}}
  \item{src.templates}{string specifying the path to folder container alternative source code templates. See details for more information.}
  \item{overwrite}{boolean specifying whether to overwrite existing files and folders.}
}

\details{
\code{new.adt} creates a skeleton project. \code{name} is used for the project name, folder names, file names and class names
so should be unique and reasonably discriptive of the project, though not very long. C++ language support is implemented
for \code{vs}, \code{libtools}, \code{xcode} and \code{autoconf} targets. Pascal language support is currently only implement for the \code{lazarus}.

\code{new.adt} creates a bare bones skeleton that does nothing but provides the backbone to make something useful. It can be useful
to have a generic skeleton project that has a base level of functionality that is to be extended in a customized implementation. The
argument \code{src.templates} allows this to take place. This argument can point to a folder containing a customized skeleton source
that will be used for the basis of any skeleton project created by \code{new.adt}. That folder must contain two subfolders, \code{cpp} and
\code{pascal}, containing all of the same files as provided in the base implementation in the ADT install. Under windows you will find it
in \code{Program files\\ADT\\templates\\source} and in Linux distributions under \code{/usr/local/share/adt/templates/source}. Use the files
found there as a basis for any new templates you make.
}

\author{
Paavo Jumppanen
}

\examples{
# Create a skeleton project called Rosenbrock targeting libtools and C++
new.adt("C:/temp", "Rosenbrock", "Rb")

# Create a skeleton project called Cryptic targeting autoconf and C++
new.adt("C:/temp", "Cryptic", "Cr", target="autoconf")

# Create a skeleton project called CustomCryptic targeting autoconf and C++ using custom templates
new.adt("C:/temp", "CustomCryptic", "CCr", target="autoconf", src.templates="C:/temp/mytemplates")
}

\keyword{adt}
