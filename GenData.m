clear;
close all;
clc;

K = 7;
input = 'stadium.bmp';
[img cmap] = imread(input);
img_rgb = ind2rgb(img, cmap);
img_double = im2double(img_rgb);

rows = size(img_double,1);
cols = size(img_double,2);
X = reshape(img_double, rows*cols, 3);
[IDX, Mu] = kmeans(X, K);

Rec= zeros(rows,cols,3);

%cnt = 0;
%for j = 1:cols
%    for i = 1:rows
%        cnt = cnt+1;
%        ind = IDX(cnt);
        
%        for c = 1:3
%            Rec(i,j,c) = Mu(ind, c);
%        end
%    end
%end

for l=1:3
    for i=1:rows
        for j=1:cols
            %img_double(i,j,l)
            fprintf('%.4f\t', img_rgb(i,j,l));
        end
        fprintf('\n');
    end
end

fig1 = figure('name','Text', 'numberTitle', 'off');
image(img_rgb(1:rows,1:cols,:));
axis equal tight

for l=1:3
    for i=31:50
        for j=51:150
            fprintf('%.4f\t', img_rgb(i,j,l));
        end
        fprintf('\n');
    end
end

fig2 = figure('name','Pattern', 'numberTitle', 'off');
image(img_rgb(31:50,51:150,:));
axis equal tight

%for i=1:rows
%    for j=1:cols
%        fprintf('%.4f\t', img_double(i,j,3));
%    end
%    fprintf('\n');
%end
%for i=1:5
%    for j=1:5
%        fprintf('%.4f\t', img_double(i,j,3));
%    end
%    fprintf('\n');
%end
%Call EM algorithm after finising kmeans.
%[h m Q] = EMG('goldy.bmp', K);