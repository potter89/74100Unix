osascript -e 'tell application "Terminal" to activate' -e 'tell application "System Events" to tell process "Terminal" to keystroke "n" using command down'
osascript -e 'tell application "Terminal" to do script "cd /Users/elvio/Library/Developer/Xcode/DerivedData/74100Unix-ejivqlvprbolfvdawfcidasrzlxk/Build/Products/Release/Results; paste -d ',' *.txt > results.csv" in selected tab of the front window'