////////////////////////////////////////////////////////////////////////////////
// taskwarrior - a command line task list manager.
//
// Copyright 2010 - 2013, Johannes Schlatow.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#define L10N                                           // Localization complete.

#include <text.h>
#include <i18n.h>
#include <TransportShell.h>
#include <util.h>

////////////////////////////////////////////////////////////////////////////////
TransportShell::TransportShell(const Uri& uri) : Transport(uri)
{
  _executable = "cp";
}

////////////////////////////////////////////////////////////////////////////////
void TransportShell::send(const std::string& source)
{
  if (_uri._path == "")
    throw std::string (STRING_TRANSPORT_SHELL_NOPATH);

  // Is there more than one file to transfer?
  // Then path has to end with a '/'
  if (is_filelist(source) && !_uri.is_directory())
    throw format (STRING_TRANSPORT_URI_NODIR, _uri._path);

  _arguments.push_back (source);

  _arguments.push_back (_uri._path);

  if (execute ())
    throw std::string (STRING_TRANSPORT_SHELL_FAIL);
}

////////////////////////////////////////////////////////////////////////////////
void TransportShell::recv(std::string target)
{
  if (_uri._path == "")
    throw std::string (STRING_TRANSPORT_SHELL_NOPATH);

  // Is there more than one file to transfer?
  // Then target has to end with a '/'
  if (is_filelist(_uri._path) && !is_directory(target))
    throw format (STRING_TRANSPORT_URI_NODIR, target);

  _arguments.push_back (_uri._path);

  _arguments.push_back (target);

  if (execute ())
    throw std::string (STRING_TRANSPORT_SHELL_FAIL);
}

////////////////////////////////////////////////////////////////////////////////
