% create pbm pgm and ppm files
a = imread('greens.jpg');
imwrite(a, 'greens_binary.pbm', 'encoding', 'rawbits');
imwrite(a, 'greens_ascii.pbm', 'encoding', 'ascii');
imwrite(a, 'greens_binary.pgm', 'encoding', 'rawbits');
imwrite(a, 'greens_ascii.pgm', 'encoding', 'ascii');
imwrite(a, 'greens_binary.ppm', 'encoding', 'rawbits');
imwrite(a, 'greens_ascii.ppm', 'encoding', 'ascii');
% show img
subplot(3,2,1);
b = my_imread('greens_binary.pbm');
imshow(b);
subplot(3,2,2);
c = my_imread('greens_ascii.pbm');
imshow(c);
subplot(3,2,3);
d = my_imread('greens_binary.pgm');
imshow(d);
subplot(3,2,4);
e = my_imread('greens_ascii.pgm');
imshow(e);
subplot(3,2,5);
f = my_imread('greens_binary.ppm');
imshow(f);
subplot(3,2,6);
g = my_imread('greens_ascii.ppm');
imshow(g);