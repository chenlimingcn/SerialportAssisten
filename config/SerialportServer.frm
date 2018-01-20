<?xml version="1.0" encoding="UTF-8"?>
<SerialportServer>
	<Device name="ps611" desc=" 充电模块">
		<Frame name="vol" desc="模拟量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 01 00 01 00 02 0D" />
			<Response value="EB 90 EB 90 08 01 00 01 02 49 92 00 2E 0D 0D" />
		</Frame>
		<Frame name="vol" desc="告警量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 04 01 00 03 00 04 0D" />
			<Response value="EB 90 EB 90 05 01 00 03 01 C2 C7 0D" />
		</Frame>
	</Device>
	<Device name="pj611" desc="绝缘监察">
	    <Frame name="vol" desc="开始巡检"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 02 00 21 00 23 0D" />
			<Response value="EB 90 EB 90 04 02 00 21 00 23 0D" />
		</Frame>
		<Frame name="vol" desc="模拟量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 02 00 01 00 03 0D" />
			<Response value="EB 90 EB 90 94 02 00 01 48 4C A5 09 87 4C A5 09 87 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 4E 20 85 0D " />
		</Frame>
		<Frame name="vol" desc="告警量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 02 00 03 00 05 0D" />
			<Response value="EB 90 EB 90 16 02 00 03 12 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 17 0D " />
		</Frame>
	</Device>
	<Device name="PB601" desc="电池巡检">
		<Frame name="vol" desc="模拟量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 03 00 01 00 04 0D" />
			<Response value="EB 90 EB 90 2C 03 00 01 14 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 EA 93 95 0D" />
		</Frame>
		<Frame name="vol" desc="状态量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 03 00 02 00 05 0D" />
			<Response value="EB 90 EB 90 07 03 00 02 03 FF FF 07 0D 0D" />
		</Frame>
	</Device>
	<Device name="PK601" desc="扩展遥信">
		<Frame name="vol" desc="状态量"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 04 00 02 00 06 0D" />
			<Response value="EB 90 EB 90 08 04 00 02 04 91 00 00 00 9B 0D" />
		</Frame>
	</Device>
	<Device name="pc611" desc="综合监控">
		<Frame name="vol" desc="模拟量查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 05 00 01 00 06 0D" />
			<Response value="EB 90 EB 90 24 05 00 01 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 49 CF 49 D3 00 00 00 00 00 00 00 00 00 00 4A 0D" />
		</Frame>
		<Frame name="vol" desc="开关信息查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 05 00 03 00 08 0D" />
			<Response value="EB 90 EB 90 05 05 00 03 01 00 09 0D" />
		</Frame>
		<Frame name="vol" desc="模拟量系数查询"><!-- 当接收到Require帧,则发送Response -->
			<Require value="EB 90 EB 90 04 05 00 44 00 49 0D" />
			<Response value="EB 90 EB 90 24 05 00 44 10 08 76 08 76 08 76 08 7F 08 7F 08 76 15 17 15 1D 15 16 02 F3 02 F0 02 F2 02 77 02 78 02 77 03 DA 0C 0D" />
		</Frame>
	</Device>
	<!-- <Device>
		<Frame>
			<Require value="EB 90 EB 90 08 02 00 22 02 00 5A 00 2D AD 0D" />
			<Response value="EB 90 EB 90 08 02 00 22 02 00 5A 00 2D AD 0D" />
		</Frame>
		<Frame>
			<Require value="EB 90 EB 90 06 02 00 23 02 00 00 27 0D" />
			<Response value="EB 90 EB 90 06 02 00 23 02 00 00 27 0D" />
		</Frame>
		<Frame>
			<Require value="EB 90 EB 90 05 02 00 24 01 00 27 0D" />
			<Response value="EB 90 EB 90 05 02 00 24 01 00 27 0D" />
		</Frame>
		<Frame>
			<Require value="EB 90 EB 90 08 01 00 13 02 5C 94 00 00 06 0D" />
			<Response value="EB 90 EB 90 08 01 00 13 02 5C 94 00 00 06 0D" />
		</Frame>
	</Device>
 --></SerialportServer>