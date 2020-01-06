import os
import sys
import re

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
    pattern = re.compile(r'\"(\b[\w/]+\b)\".*@([0-9a-f]+)')
    with open(path + '_tmp', 'w') as wf:
        for line in open(path):
            if '@' in line and 'url' not in line and '/v8.git' not in line:
                gs = re.search(pattern, line)
                if gs:
                    directory = gs.group(1)
                    commithash = gs.group(2)
                    repo, commithashNew = dict[directory].split('@', 1)
                    print directory + " from " + commithash + " to "+ commithashNew
                    line = line.replace(commithash, commithashNew)
            wf.writelines(line)
    os.remove(path)
    os.rename(path + '_tmp',path)

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
    parse_dict_to_file(DEFAULT_DEPS_GITEE_PATH, dependencies_gitee)
    parse_dict_to_file(DEFAULT_DEPS_GITHUB_PATH, dependencies_github)

if __name__ == '__main__':
  exit(main(sys.argv[1:]))