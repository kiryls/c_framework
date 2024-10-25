f := .

.PHONY: git
git:
	git add $f
	git commit -m "$(msg)"
	git push origin main
