import os
import sys
import subprocess
import threading

DEFAULT_DEPS_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS'))
DEFAULT_DEPS_GITEE_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS-gitee'))
DEFAULT_DEPS_GITHUB_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS-github'))

def git_executable():
  """Find the git executable.

  Returns:
      A string suitable for passing to subprocess functions, or None.
  """
  envgit = os.environ.get('GIT_EXECUTABLE')
  searchlist = ['git']
  if envgit:
    searchlist.insert(0, envgit)
  with open(os.devnull, 'w') as devnull:
    for git in searchlist:
      try:
        subprocess.call([git, '--version'], stdout=devnull)
      except (OSError,):
        continue
      return git
  return None

def parse_file_to_dict(path):
    dictionary = {}
    execfile(path, dictionary)
    return dictionary
def git_push_to_repository(git, repo, commithash, directory, verbose):
    subprocess.check_call(
      [git, 'push', '--all', repo], cwd=directory)
    if verbose:
      status(directory, commithash, True)
    return

def status(directory, commithash, change):
  def truncate(s, length):
    return s if len(s) <= length else s[:(length - 3)] + '...'
  dlen = 36
  directory = truncate(directory, dlen)
  commithash = truncate(commithash, 40)
  symbol = '>' if change else '@'
  sys.stdout.write('%-*s %s %s\n' % (dlen, directory, symbol, commithash))

def git_upload_deps(deps_file_path, verbose):
    git = git_executable()
    assert git
    deps_file_directory = os.path.dirname(deps_file_path)
    deps_file = parse_file_to_dict(deps_file_path)
    dependencies = deps_file['deps'].copy()
    
    list_of_arg_lists = []
    for directory in sorted(dependencies):
        if not isinstance(dependencies[directory], basestring):
            if verbose:
              print 'Skipping "%s".' % directory
            continue
        if '@' in dependencies[directory]:
          repo, commithash = dependencies[directory].split('@', 1)
        relative_directory = os.path.join(deps_file_directory, directory)
        list_of_arg_lists.append(
          (git, repo, commithash, relative_directory, verbose))
    
    multithread(git_push_to_repository, list_of_arg_lists)
    return 0
def multithread(function, list_of_arg_lists):
  # for args in list_of_arg_lists:
  #   function(*args)
  # return
  threads = []
  for args in list_of_arg_lists:
    thread = threading.Thread(None, function, None, args)
    thread.start()
    threads.append(thread)
  for thread in threads:
    thread.join()
def main(argv):  
    git_upload_deps(DEFAULT_DEPS_GITEE_PATH, True)
    git_upload_deps(DEFAULT_DEPS_GITHUB_PATH, True)
    return 0
if __name__ == '__main__':
  exit(main(sys.argv[1:]))