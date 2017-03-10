for i in {1..49}
do
	convert -crop 1920x540+0+0 -rotate 180 a/image${i}.png a/image${i}-cropped.png
	convert -crop 1920x540+0+0 b/image${i}.png b/image${i}-cropped.png
	convert b/image${i}-cropped.png a/image${i}-cropped.png -append image${i}-merged.png
	rm ./*/*cropped.png
done
