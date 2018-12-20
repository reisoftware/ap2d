entry {
	book = {
		name = [[test-]],
		sheets = {
			{
				name = [[t-]],
				cell_ws = {
					{
						col = [[a]],
						size = 2.75,
					},
					{
						col = [[g]],
						size = 1.5,
					},
					{
						col = [[i]],
						size = 1.75,
					},
					{
						col = [[j]],
						size = 6.38,
					},
					{
						col = [[k]],
						size = 5.63,
					},
					{
						col = [[l]],
						size = 2.13,
					},
					{
						col = [[m]],
						size = 2,
					},
					{
						col = [[n]],
						size = 0.46,
					},
					{
						col = [[o]],
						size = 1.75,
					},
					{
						col = [[p]],
						size = 3.63,
					},
					{
						col = [[q]],
						size = 1.88,
					},
					{
						col = [[v]],
						size = 2,
					},
					{
						col = [[x]],
						size = 2.5,
					},
					{
						col = [[z]],
						size = 2.38,
					},
					{
						col = [[ab]],
						size = 2.25,
					},
					{
						col = [[ac]],
						size = 2,
					},
					{
						col = [[ad]],
						size = 2.13,
					},
					{
						col = [[af]],
						size = 2,
					},
					{
						col = [[ag]],
						size = 2.15,
					},
					{
						col = [[ah]],
						size = 2,
					},
					{
						col = [[ai]],
						size = 1.88,
					},
					{
						col = [[ak]],
						size = 2,
					},
					{
						col = [[al]],
						size = 3.5,
					},
					{
						col = [[an]],
						size = 2,
					},
					{
						col = [[ao]],
						size = 3.75,
					},
					{
						col = [[ap]],
						size = 2,
					},
					{
						col = [[aq]],
						size = 2.25,
					},
					{
						col = [[ar]],
						size = 3.13,
					},
					{
						col = [[at]],
						size = 2,
					},
					{
						col = [[au]],
						size = 3,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 16,
					},
					{
						id = 2,
						size = 12,
					},
					{
						id = 5,
						size = 20,
					},
					{
						id = 6,
						size = 22.5,
					},
					{
						id = 7,
						size = 16,
					},
					{
						id = 10,
						size = 14,
					},
					{
						id = 11,
						size = 18,
					},
					{
						id = 12,
						size = 14,
					},
					{
						id = 21,
						size = 18,
					},
					{
						id = 22,
						size = 14,
					},
					{
						id = 23,
						size = 11,
					},
					{
						id = 24,
						size = 12,
					},
					{
						id = 29,
						size = 17,
					},
					{
						id = 30,
						size = 5,
					},
					{
						id = 34,
						size = 13,
					},
				},
				pos_rule = [[
					set_start_x(1);
					set_start_y(1);
				]],
				tables = {
					{
						type = 1,
						border = 0,
						init_rule = [[]],
						filter_rule = [[]],
						group_rule = [[]],
						sort_rule = [[]],
						cells = {
							{
								content = [[部品記号]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[set_cell_pos("a1:b1");]],
								border = 1,
							},
							{
								content = [[数量]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[単長さ]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[総長さ]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[単重]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[総重]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[備考]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
						},
					},
					{
						type = 1,
						border = 0,
						init_rule = [[]],
						filter_rule = [[]],
						group_rule = [[group_by_part_no();]],
						sort_rule = [[sort_by_section();]],
						cells = {
							{
								content = [[部品記号]],
								content_rule = [[content_by_no();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(2);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[数量]],
								content_rule = [[content_by_count();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[単長さ]],
								content_rule = [[content_by_length();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[総長さ]],
								content_rule = [[content_by_lengths_sum();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[単重]],
								content_rule = [[content_by_weight();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[総重]],
								content_rule = [[content_by_weight_sum();]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
							{
								content = [[備考]],
								content_rule = [[]],
								style = [[文字-12]],
								pos_rule = [[									
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
								border = 1,
							},
						},
					},
				},
			},
		},
		style_db = {
			css = {
				{
					type = 0,
					name = [[文字-14]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 14,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
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

