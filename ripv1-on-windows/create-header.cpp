//RIP用のヘッダーを生成し配列として返す関数
/*
*0                           16                       31
*+-------------+-------------+------------------------+
*|command(8bit)|version(8bit)|0(16bit)                |
*+---------------------------+------------------------+
*|afi(16bit)                 |0(16bit)                |
*+----------------------------------------------------+
*                                                     63
*/
unsigned __int32* generate_rip_header(int command, int version, int afi) {
	unsigned __int32 head[2] = { 0 };
	unsigned long int head1 = 0x0000;
	unsigned long int head2 = 0x0000;

	head1 = head1 | command;
	head1 = head1 << 8;
	head1 = head1 | version;
	head1 = head1 << 16;

	head2 = head2 | afi;
	head2 = head2 << 16;

	head[0] = head1;
	head[1] = head2;

	return head;
}

//RIP用のIPAddressを含むヘッダーを生成
/*
0
+----------------------------------------------------+
|IP Address(32bit)                                   |
+----------------------------------------------------+
|0(32bit)                                            |
+----------------------------------------------------+
|0(32bit)                                            |
+----------------------------------------------------+
|metric(32bit)                                       |
+----------------------------------------------------+
*/
unsigned __int32* generate_rip_header_ip(unsigned __int32 ip_addr, unsigned __int32 metric) {
	unsigned __int32 head[4] = { 0 };
	head[0] = ip_addr;
	head[3] = metric;

	return head;
}