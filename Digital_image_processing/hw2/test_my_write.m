% create pbm pgm and ppm files
a = imread('greens.jpg');
my_imwrite(a, 'greens_binary.pbm', 'rawbits');
my_imwrite(a, 'greens_ascii.pbm', 'ascii');
my_imwrite(a, 'greens_binary.pgm', 'rawbits');
my_imwrite(a, 'greens_ascii.pgm', 'ascii');
my_imwrite(a, 'greens_binary.ppm', 'rawbits');
my_imwrite(a, 'greens_ascii.ppm', 'ascii');
% show img
subplot(3,2,1);
b = imread('greens_binary.pbm');
imshow(b);
subplot(3,2,2);
c = imread('greens_ascii.pbm');
imshow(c);
subplot(3,2,3);
d = imread('greens_binary.pgm');
imshow(d);
subplot(3,2,4);
e = imread('greens_ascii.pgm');
imshow(e);
subplot(3,2,5);
f = imread('greens_binary.ppm');
imshow(f);
subplot(3,2,6);
g = imread('greens_ascii.ppm');
imshow(g);