entry {
	book = {
		name = [[book-test.xls]],
		sheets = {
			{
				name = [[酷睿]],
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
						border = 1,
						pos_rule = [[
							set_table_x(1);
							set_table_y(1);
						]],
						init_rule = [[]],
						filter_rule = [[]],
						group_rule = [[]],
						sort_rule = [[]],
						cells = {
							{
								w = 18,
								h = 5,
								content = [[部件号]],
								content_rule = [[]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								w = 32,
								content = [[数量]],
								content_rule = [[]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								w = 10.5,
								content = [[尺寸]],
								content_rule = [[]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(3);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								w = 8.5,
								content = [[重量]],
								content_rule = [[]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(4);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
						},
					},
					{
						type = 1,
						border = 1,
						pos_rule = [[
							set_table_x(1);
							set_table_y(2);
						]],
						init_rule = [[add_part(NULL);]],
						filter_rule = [[]],
						group_rule = [[group_by_section();]],
						sort_rule = [[sort_by_section();]],
						cells = {
							{
								h = 5,
								content = [[]],
								content_rule = [[content_by_part_no();]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[]],
								content_rule = [[content_by_count();]],
								style = [[整数]],
								pos_rule = [[
									set_cell_x(2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[]],
								content_rule = [[content_by_length_sum();]],
								style = [[小数]],
								pos_rule = [[
									set_cell_x(3);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[]],
								content_rule = [[content_by_weight_sum();]],
								style = [[小数]],
								pos_rule = [[
									set_cell_x(4);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
						},
					},
					{
						type = 1,
						border = 1,
						pos_rule = [[
							set_table_x(1);
							set_table_y(get_last_y()+1);
						]],
						init_rule = [[add_part(NULL);]],
						group_rule = [[equ();]],
						cells = {
							{
								h = 5,
								content = [[合计]],
								style = [[文字]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[]],
								content_rule = [[content_by_weight_sum();]],
								style = [[小数]],
								pos_rule = [[
									set_cell_x(2);
									set_cell_y(get_last_y());
									set_cell_w(3);
									set_cell_h(1);
								]],
							},
						},
					},
				},
			},
		},
		style_db = {
			css = {
				{
					name = [[文字]],
					font = [[宋体]],
					text_color = 3,
					back_color = 0,
					size = 3.5,
					blod = 1,
					italic = 0,
					h_allign = 3,
					v_allign = 2,
				},
				{
					name = [[整数]],
					font = [[宋体]],
					text_color = 1,
					back_color = 35,
					size = 3.5,
					blod = 0,
					italic = 0,
					h_allign = 1,
					v_allign = 2,
					precision = 1,
					bit = 0,
					addends = 0,
				},
				{
					name = [[小数]],
					font = [[宋体]],
					text_color = 5,
					back_color = 35,
					size = 3.5,
					blod = 0,
					italic = 1,
					h_align = 4,
					v_align = 2,
					precision = 0.5,
					bit = 1,
					addends = 1,
				},
			},
		},
	},
}

