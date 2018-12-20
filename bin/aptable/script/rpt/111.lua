--------------------- Standard edition for Daiwa House--------------------------------
--[[

]]--


entry {
	book = { --整个Excel文件
		name = [[GSimpleBeam-]],						--文件名（暂时无用）
		sheets = {										--多个页的集合
			{											--第一页（如果有第二页从这里复制）
				name = [[GSimpleBeam-]],				--页名前缀
				cell_ws = {								--设置列宽
					{
						col = [[A]],
						size = 1.88
					},									--缺省与上列相同
					{
						col = [[E]],
						size = 5.75,
					},
					{
						col = [[F]],
						size = 1.88,
					},
					{
						col = [[G]],
						size =1.75,
                                         },									--缺省与上列相同
					{       
						col = [[I]],
						size = 3.63,
					},									--缺省与上列相同
					{
						col = [[J]],
						size = 1.38,
					},
					{
						col = [[L]],
						size = 1.88
					},
					{
						col = [[M]],
						size =4.5,
                                                
						col = [[N]],
						size =4.88
					},									--缺省与上列相同
					{
						col = [[O]],
						size = 1.13,
					},
					{
						col = [[P]],
						size = 0.15,
					},
					{
						col = [[Q]],
						size =1.75,
                                         },									--缺省与上列相同
					{       
						col = [[R]],
						size =1.25,
					},									--缺省与上列相同
					{
						col = [[S]],
						size = 1.88,
					},
					{
						col = [[U]],
						size = 3
					},
					{
						col = [[V]],
						size =2.75,

                                                col = [[W]],
						size = 3.13
					},									--缺省与上列相同
					{
						col = [[X]],
						size = 2.25,
					},
					{
						col = [[Z]],
						size = 1.88,
					},
					{
						col = [[AA]],
						size =2.5,
                                         },									--缺省与上列相同
					{       
						col = [[AD]],
						size = 2.38,
					},									--缺省与上列相同
					{
						col = [[AE]],
						size = 1.88,
					},
					{
						col = [[AF]],
						size = 2.63
					},
					{
						col = [[AG]],
						size =2.5,
                                                
						col = [[AH]],
						size =5
					},
				},
				cell_hs = {								--设置行高
					{
						id = 1,
						size = 13.5,						--缺省与上行相同
					},
					{
						id = 3,
						size =14.25,
					},
					{
						id = 4,
						size = 13.5,
					},
					{
						id = 5,
						size = 14.5,
					},
					{
						id = 6,
						size = 13.5,
					},
					{
						id = 8,
						size = 21.75,

                                                id = 9,
						size = 13.5,						--缺省与上行相同
					},
					{
						id =10,
						size =16.5,
					},
					{
						id = 11,
						size = 13.5,
					},
					{
						id = 12,
						size = 12.75,
					},
					{
						id =22,
						size = 16,
					},
					{
						id = 27,
						size = 21,
					},
				},

--设置整个页的起始位置
--列
--行
				pos_rule = [[
					set_start_x(1);	
					set_start_y(1);	
				]],
				tables = {								--表的集合
					{									--第一个表（无数据）
						type = 1,						--表的类型 1表示单表（可独立处理数据） 2表示复合表（表的集合）
						border = 0,						--表的边界线类型设定
						init_rule = [[]],				--表中数据的初始化规则（内容为空）
						filter_rule = [[]],				--表中数据的过滤规则
						group_rule = [[]],				--表中数据的分组规则
						sort_rule = [[]],				--表中数据的排序规则
						cells = {						--表的列的集合
							{							--第一列
								content = [[№]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("Z2:AH2");]],
								border = 1,
							},							--第二列
							{
								content = [[発信日 ]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("Z3:AA3");]],
								border = 1,
							},

							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("AB3:AH3");]],
								border = 1,
							},
							{
								content = [[様]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("I5:I5");]],
								border = 0,
							},
							{
								content = [[規格プレート　発注書]],
								content_rule = [[]],
								style = [[文字-18]],
								pos_rule = [[set_cell_pos("A8:AH8");]],
								border = 0,
							},
							{
								content = [[発注№]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("X10:AA10");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("AB10:AG10");]],
								border = 1,
							},
							{
								content = [[依頼№]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("X12:AG12");]],
								border = 1,
							},
							{
								content = [[作成:]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("X14:Z14");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("AA14:AG14");]],
								border = 1,
							},
							{
								content = [[工事名:]],
								content_rule = [[]],
								style = [[文字-14]],
								pos_rule = [[set_cell_pos("A22:D22");]],
								border = 0,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-13]],
								pos_rule = [[set_cell_pos("E22:I23");]],
								border = 1,
							},
							{
								content = [[工区]],
								content_rule = [[]],
								style = [[文字-14]],
								pos_rule = [[set_cell_pos("J22:M23");]],
								border = 1,
							},
								{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("N22:R23");]],
								border = 1,
							},
								{
								content = [[優先順位]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("S22:U22");]],
								border = 1,
							},
							{
								content = [[－]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("S23:U23");]],
								border = 1,
							},
							{
								content = [[希望納期]],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("V22:X23");]],
								border = 1,
							},
							{
								content = [[　平成  　年  月  日],
								content_rule = [[]],
								style = [[文字-11]],
								pos_rule = [[set_cell_pos("Z22:AH23");]],
								border = 1,
							},
							{
								content = [[納　　入　　先]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("A24:E24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("F24:I24");]],
								border = 1,
							},
								{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("J24:M24");]],
								border = 1,
							},
								{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("N24:Q24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("R24:U24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("V24:X24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("Z24:AB24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("AD24:AF24");]],
								border = 1,
							},
							{
								content = [[班]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("AG24:AH24");]],
								border = 1,
							},
							{
								content = [[工　　場　　名]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("A25:E25");]],
								border = 1,
							},
							{
							content = [[加工班名記入]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("A26:E26");]],
								border = 1,
							},
							{
								content = [[規　格　記　号]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("A27:J27");]],
								border = 1,
							},
							{
								content = [[単重]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("L27:Q27");]],
								border = 1,
							},

							{
								content = [[数量]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("R27:V27");]],
								border = 1,
							},
							{
								content = [[総重],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("W27:AA27");]],
								border = 1,
							},
							{
								content = [[備　　　考]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("AB27:AH27");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("A28:J28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("L28:Q28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("R28:V28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("W28:AA28");]],
								border = 1,
							},
							{
								 
							},

						},
					},
				},
			},
		},
		style_db = {									--整个文件的样式库
			css = {										--样式的集合
				{										--第一种样式
					type = 0,							--类型
					name = [[文字-14]],					--样式名
					font = [[ＭＳ 明朝]],				--样式字体
					text_color = 1,						--文字颜色
					back_color = 0,						--背景颜色
					size = 14,							--字号
					blod = 0,							--加粗
					italic = 0,							--斜体字
					h_align = 3,						--水平对齐
					v_align = 2,						--垂直对齐
				},
				{
					type = 0,
					name = [[文字-12]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 12,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 3,
				},
				{
					type = 0,
					name = [[文字-10]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 10,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[文字-9]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 9,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[文字-8]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 8,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[文字-7]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 7,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
			},
		},
	},
}

