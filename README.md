HSV 
- stream : 웹캠으로 받은 영상을 imgmsg 형태의 토픽으로 발행한다. 해당 영상의 정보(높이, 너비, fps)를 별도의 메시지로 발행한다.
- record : imgmsg를 수신하여 임의의 높이, 너비, fps의 정보로 녹화한다.
- record_autoForm : imgmsg로 받은 영상을 별도의 메시지로 수신한 영상 정보로 녹화한다. 
- 
