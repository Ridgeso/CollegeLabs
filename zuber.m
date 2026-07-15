clear; clc; close all;

im = double(imread('zubr.jpg')) / 255.0;

imshow(im);

figure;

redChanel = im;
greenChanel = im;
blueChanel = im;
grayscale = im;

redChanel(:, :, [2, 3]) = 0;
greenChanel(:, :, [1, 3]) = 0;
blueChanel(:, :, [1, 2]) = 0;
grayscale = mean(grayscale, 3);

w = 2; h = 2;
subplot(w,h,1);
imshow(redChanel);
subplot(w,h,2);
imshow(greenChanel);
subplot(w,h,3);
imshow(blueChanel);
subplot(w,h,4);
imshow(grayscale);

figure

w = 3; h = 2;
subplot(w,h,1);
imshow(im(:, :, 1));
subplot(w,h,3);
imshow(im(:, :, 2));
subplot(w,h,5);
imshow(im(:, :, 3));

subplot(w, h, 2);
imhist(im(:, :, 1));
subplot(w, h, 4);
imhist(im(:, :, 2));
subplot(w, h, 6);
imhist(im(:, :, 3));

figure

YUV = [.299, 0.587, .114];
YUV = permute(YUV, [1, 3, 2]);
% waged = sum(im .* YUV, 3);
waged = rgb2gray(im);

w = 4; h = 3;

subplot(w, h, 1);
imshow(waged);
subplot(w, h, 2);
imhist(waged);

subplot(w, h, 4);
jasnosc = waged + 0.2;
jasnosc(jasnosc > 1) = 1;
jasnosc(jasnosc < 0) = 0;
imshow(jasnosc);
subplot(w, h, 5);
imhist(jasnosc);
subplot(w, h, 6);
x = 0 : 1/255 : 1;
y = x + 0.2;
y(y>1) = 1;
y(y<0) = 0;
plot(x, y);
ylim([0, 1]);

subplot(w, h, 7);
c = 2;
contrast = waged * c;
imshow(contrast);
subplot(w, h, 8);
imhist(contrast);
subplot(w, h, 9);
x = 0 : 1/255 : 1;
y = c*x;
y(y>1) = 1;
y(y<0) = 0;
plot(x, y);
ylim([0,1]);

subplot(w, h, 10);
g = 2;
gamma = waged .^ g;
imshow(gamma);
subplot(w, h, 11);
imhist(gamma);
subplot(w, h, 12);
x = 0 : 1/255 : 1;
y = x .^ g;
y(y>1) = 1;
y(y<0) = 0;
plot(x, y);
ylim([0, 1]);

figure

subplot(1, 2, 1);
him = histeq(im);
imshow(him);
subplot(1, 2, 2);
imhist(him);

pause;
close all;