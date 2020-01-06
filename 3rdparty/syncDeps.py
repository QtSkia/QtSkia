import os
import subprocess
import sys
import threading

DEFAULT_DEPS_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS'))
DEFAULT_DEPS_GITEE_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS-gitee'))
DEFAULT_DEPS_GITHUB_PATH = os.path.normpath(
  os.path.join(os.path.dirname(__file__), 'skia', 'DEPS-github'))


def parse_file_to_dict(path):
    dictionary = {}
    execfile(path, dictionary)
    return dictionary
def parse_dict_to_file(path, dict):
    f = open(path,'w')
    f.write(str(dict))
    f.close()
def main(argv):
    deps_file = parse_file_to_dict(DEFAULT_DEPS_PATH)
    dependencies = deps_file['deps'].copy()
    
    deps_file_gitee = parse_file_to_dict(DEFAULT_DEPS_GITEE_PATH)
    dependencies_gitee = deps_file_gitee['deps'].copy()
    
    deps_file_github = parse_file_to_dict(DEFAULT_DEPS_GITHUB_PATH)
    dependencies_github = deps_file_github['deps'].copy()

    for directory in sorted(dependencies):
        if '@' in dependencies[directory]:
            repo, commithash = dependencies[directory].split('@', 1)
            if '@' in dependencies_gitee[directory]:
                repo_gitee,commithash_gitee = dependencies_gitee[directory].split('@', 1)
                if commithash_gitee != commithash:
                    dependencies_gitee[directory] = repo_gitee + '@'+ commithash
                    print 'gitee {0} from {1} to {2}'.format(directory, commithash_gitee, commithash)
            if '@' in dependencies_github[directory]:
                repo_github,commithash_github = dependencies_github[directory].split('@', 1)
                if commithash_github != commithash:
                    dependencies_github[directory] = repo_github + '@'+ commithash
                    print 'github {0} from {1} to {2}'.format(directory, commithash_github, commithash)
    deps_file_gitee['deps'] = dependencies_gitee
    parse_dict_to_file(DEFAULT_DEPS_GITEE_PATH, deps_file_gitee)
    deps_file_github['deps'] = dependencies_github
    parse_dict_to_file(DEFAULT_DEPS_GITHUB_PATH, deps_file_github)
if __name__ == '__main__':
  exit(main(sys.argv[1:]))