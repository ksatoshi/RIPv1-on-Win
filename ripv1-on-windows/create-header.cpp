unsigned* reset_header(unsigned*, int);

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
unsigned* generate_rip_header(unsigned *header,int header_length,int command, int version, int afi) {
	//ヘッダーを0でリセット
	header = reset_header(header, header_length);

	//header_length==2の場合のみRIPヘッダーを作成して返す
	if (header_length == 2) {
		unsigned long int head1 = 0x00000000;
		unsigned long int head2 = 0x00000000;

		head1 = head1 | command;
		head1 = head1 << 8;
		head1 = head1 | version;
		head1 = head1 << 16;

		head2 = head2 | afi;
		head2 = head2 << 16;

		*header = head1;
		*(header + 1) = head2;
	}

	return header;
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
unsigned* generate_rip_header_ip(unsigned* header, int header_length, unsigned __int32 ip_addr, unsigned __int32 metric) {
	//ヘッダーをリセット
	header = reset_header(header, header_length);

	//header_length==4の場合のみIPヘッダーを作成
	if (header_length == 4) {
		*header = ip_addr;
		*(header + 3) = metric;
	}

	return header;
}

//ヘッダーを0にリセットする関数
unsigned* reset_header(unsigned* header, int length) {
	for (int i = 0; i < length; i++) {
		*(header + i) = 0x00000000;
	}
	return header;
}