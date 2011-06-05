git add -A
echo -n 'Comment: '
read line
git commit -m "${line}"
#git remote add origin git@github.com:stinky-nnov/kd.git
git push origin master