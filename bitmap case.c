if(F[0]==A[0] && F[1]==0)
{
jpegWrite(01);
}
if(F[0]==A[1] && F[1]==0)
{
jpegWrite(02);
}
if(F[0]==A[2] && F[1]==0)
{
jpegWrite(03);
}
if(F[0]==A[3] && F[1]==0)
{
jpegWrite(04);
}
if(F[0]==A[4] && F[1]==0)
{
jpegWrite(05);
}
if(F[0]==A[5] && F[1]==0)
{
jpegWrite(06);
}

//빨간 카드끼리  
if(F[0]==A[0] && F[1]==A[0])
{
jpegWrite(11);
}
if(F[0]==A[1] && F[1]==A[0])
{
jpegWrite(12);
}
if(F[0]==A[2] && F[1]==A[0])
{
jpegWrite(13);
}
if(F[0]==A[0] && F[1]==A[1])
{
jpegWrite(21);
}
if(F[0]==A[1] && F[1]==A[1])
{
jpegWrite(22);
}
if(F[0]==A[2] && F[1]==A[1])
{
jpegWrite(23);
}
if(F[0]==A[0] && F[1]==A[2])
{
jpegWrite(31);
}
if(F[0]==A[1] && F[1]==A[2])
{
jpegWrite(32);
}
if(F[0]==A[2] && F[1]==A[2])
{
jpegWrite(33);
}

// 위에 노랑 아래 빨강 
if(F[0]==A[3] && F[1]==A[0])
{
jpegWrite(14);
}
if(F[0]==A[4] && F[1]==A[0])
{
jpegWrite(15);
}
if(F[0]==A[5] && F[1]==A[0])
{
jpegWrite(16);
}
if(F[0]==A[3] && F[1]==A[1])
{
jpegWrite(24);
}
if(F[0]==A[4] && F[1]==A[1])
{
jpegWrite(25);
}
if(F[0]==A[5] && F[1]==A[1])
{
jpegWrite(26);
}
if(F[0]==A[3] && F[1]==A[2])
{
jpegWrite(34);
}
if(F[0]==A[4] && F[1]==A[2])
{
jpegWrite(35);
}
if(F[0]==A[5] && F[1]==A[2])
{
jpegWrite(36);
}

// 위에 빨강 아래 노랑 
if(F[0]==A[0] && F[1]==A[3])
{
jpegWrite(41);
}
if(F[0]==A[1] && F[1]==A[3])
{
jpegWrite(42);
}
if(F[0]==A[2] && F[1]==A[3])
{
jpegWrite(43);
}
if(F[0]==A[0] && F[1]==A[4])
{
jpegWrite(51);
}
if(F[0]==A[1] && F[1]==A[4])
{
jpegWrite(52);
}
if(F[0]==A[2] && F[1]==A[4])
{
jpegWrite(53);
}
if(F[0]==A[0] && F[1]==A[5])
{
jpegWrite(61);
}
if(F[0]==A[1] && F[1]==A[5])
{
jpegWrite(62);
}
if(F[0]==A[2] && F[1]==A[5])
{
jpegWrite(63);
}

//노랑 카드끼리 
if(F[0]==A[3] && F[1]==A[3])
{
jpegWrite(44);
}
if(F[0]==A[4] && F[1]==A[3])
{
jpegWrite(45);
}
if(F[0]==A[5] && F[1]==A[3])
{
jpegWrite(46);
}
if(F[0]==A[3] && F[1]==A[4])
{
jpegWrite(54);
}
if(F[0]==A[4] && F[1]==A[4])
{
jpegWrite(55);
}
if(F[0]==A[5] && F[1]==A[4])
{
jpegWrite(56);
}
if(F[0]==A[3] && F[1]==A[5])
{
jpegWrite(64);
}
if(F[0]==A[4] && F[1]==A[5])
{
jpegWrite(65);
}
if(F[0]==A[5] && F[1]==A[5])
{
jpegWrite(66);
}
