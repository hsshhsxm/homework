% imread()参数为文件路径
im = imread('greens.jpg');
% 将图片从jpg格式转换为ppm格式并保存，'encoding'-'rawbits'表示二进制编码，'encoding'-'ascii'表示ASCII编码
imwrite(im, 'greens_binary.ppm', 'encoding', 'rawbits');
imwrite(im, 'greens_ascii.ppm', 'encoding', 'ascii');
% 展示ppm图片
a = imread('greens_binary.ppm');
subplot(2,1,1);
imshow(a);
b = imread('greens_ascii.ppm');
subplot(2,1,2);
imshow(b);