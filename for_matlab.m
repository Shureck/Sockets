t = tcpip('0.0.0.0', 7777, 'NetworkRole', 'server');
fopen(t);
while(1)
   if(t.BytesAvailable>0)
      data = fread(t,t.BytesAvailable);
      q = char(data)
   end
   
   fwrite(t, "Test");
   pause(2);
end
