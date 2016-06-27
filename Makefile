all:
	gcc ImageMerge.c PatternMatcher/PatternMatcher.c PositionTree/PositionTree.c -o Merge
clean:
	rm -f Merge
	rm -f result.txt
