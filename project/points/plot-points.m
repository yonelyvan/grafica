data = load('points.txt');
xx=data(:,1);
yy=data(:,2);
zz=data(:,3);


size = 8;
color=[0 128 0];
%set(gcf,'Color',[0,0,0]) 
scatter3(xx, yy, zz, size,color)
%mesh(xx,yy,zz)

%plot3(xx,yy,zz,'*')