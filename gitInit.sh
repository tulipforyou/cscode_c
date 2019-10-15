#/bin/bash
#git初始化步骤

echo "Designed by sch" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/tulipforyou/cscode_c.git
git push -u origin master
