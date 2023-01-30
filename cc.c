//获取按键状态
data = *P_IOE_Data;
if ((data & 0x0080)) {
  IOE_lock = 0;
}
if ((data & 0x0080) == 0) {
  if (IOE_lock == 0) {
    play_sound_hightolow(0x33, Vol_value);
  }
  IOE_lock = 1;
}

if ((data & 0x0080))
表示按键没有被按下，此时按键锁标志为0，staic类型将记录这个标志变量的值，当if(
    (data & 0x0080) == 0)
    时，按键此时被按下了，我要判断按键锁标志是否为0，如果为1，那么程序肯定不会运行play_sound_hightolow()；这个函数，所以当按下按键的时候，锁的初始化值为0，喇叭发出声音码，音频解码器读出对应的键值为0x33。读完之后立马的将锁标志置1，如果此时一直按住按键不放，因为锁标志等于1，所以无效，程序不进入发码的状态。当松开后，按键的状态由1变成0，此时再按下按键，又有效，然后锁住。

    这样做的好处就是使按键按下的时候，发码的状态只触发一次，就不会连着发出0x33的声音码了，只发了一次。在合适的开发利用好标志锁，可以很方便的高效解决很多问题。
