X = load('result.txt');
rgb = zeros(67,200,3);
rgb(:,:,1) = X(1:67,:);
rgb(:,:,2) = X(68:134,:);
rgb(:,:,3) = X(135:201,:);
fig1 = figure('name','Compressed Image from kmeans', 'numberTitle', 'off');
image(rgb);
axis equal tight