entry {
	Book = {
		name = [[C.xls]],
		sheets = {
			{
				name = [[C]],
				cell_ws = {
					{
						col = [[a]],
						size = 2.75,
					},
					{
						col = [[b]],
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
						col = [[r]],
						size = 2,
					},
					{
						col = [[w]],
						size = 2.5,
					},
					{
						col = [[y]],
						size = 2.38,
					},
					{
						col = [[aa]],
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
						col = [[aj]],
						size = 2,
					},
					{
						col = [[al]],
						size = 3.5,
					},
					{
						col = [[am]],
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
						col = [[as]],
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
						id = 3,
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
						id = 8,
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
						id = 23,
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
						id = 25,
						size = 17,
					},
					{
						id = 30,
						size = 5,
					},
					{
						id = 31,
						size = 13,
					},
				},
				pos_rule = [[]],
				tables = {
					{
						type = 2,
						border = 0,
						sheet = 1,
						pos_rule = [[
							set_cur_x(1);
							set_cur_y(12);
						]],
						init_rule = [[add_all();]],
						filter_rule = [[g_filter();]],
						group_rule = [[group_by_kind_group_section_mat();]],
						sort_rule = [[]],
						newsheet_rule = [[newsheet_by_row(25);]],
						tables = {
							{
								type = 1,
								border = 0,
								init_rule = [[add_all();]],
								filter_rule = [[g_filter_by_super_kind_group_section_mat();]],
								group_rule = [[equ();]],
								cells = {
									{
										content = [[KIND]],
										content_rule = [[content_by_kind();]],
										style = [[文字-12]],
										pos_rule = [[set_cell_pos("AD5:AJ5");]],
										border = 1,
									},
									{
										content = [[GROUP]],
										content_rule = [[content_by_group();]],
										style = [[文字-12]],
										pos_rule = [[set_cell_pos("AD6:AJ6");]],
										border = 1,
									},
									{
										content = [[SECTION]],
										content_rule = [[content_by_section();]],
										style = [[文字-12]],
										pos_rule = [[set_cell_pos("D4:Q4");]],
										border = 1,
									},
									{
										content = [[MAT]],
										content_rule = [[content_by_mat();]],
										style = [[文字-12]],
										pos_rule = [[set_cell_pos("U4:Z4");]],
										border = 1,
									},
									{
										content = [[]],
										content_rule = [[]],
										style = [[文字-12]],
										pos_rule = [[set_cell_pos("A12:A12");]],
										border = 1,
									},
								},
							},
							{
								type = 1,
								border = 0,
								init_rule = [[add_all();]],
								filter_rule = [[g_filter_by_super_kind_group_section_mat();]],
								group_rule = [[group_by_part_no();]],
								sort_rule = [[sort_by_part_no();]],
								newsheet_rule = [[newsheet_by_row(25);]],
								cells = {
									{
										content = [[部品記号]],
										content_rule = [[content_by_part_no();]],
										style = [[文字-12]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_cur_y()+1);
											set_cell_w(3);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[長さ]],
										content_rule = [[content_by_length();]],
										style = [[数字-12]],
										pos_rule = [[
											set_cell_x(get_cur_x()+1);
											set_cell_y(get_cur_y());
											set_cell_w(7);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[単重]],
										content_rule = [[content_by_weight();]],
										style = [[数字-12]],
										pos_rule = [[
											set_cell_x(get_cur_x()+1);
											set_cell_y(get_cur_y());
											set_cell_w(2);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[数量]],
										content_rule = [[content_by_count();]],
										style = [[数字-12]],
										pos_rule = [[
											set_cell_x(get_cur_x()+1);
											set_cell_y(get_cur_y());
											set_cell_w(2);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[総重]],
										content_rule = [[content_by_weight_sum();]],
										style = [[数字-12]],
										pos_rule = [[
											set_cell_x(get_cur_x()+1);
											set_cell_y(get_cur_y());
											set_cell_w(2);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[備考]],
										content_rule = [[set_content_s("");]],
										style = [[文字-9]],
										pos_rule = [[
											set_cell_x(get_cur_x()+1);
											set_cell_y(get_cur_y());
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
				{
					type = 1,
					name = [[数字-12]],
					font = [[ＭＳ 明朝]],
					text_color = 1,
					back_color = 0,
					size = 12,
					blod = 0,
					italic = 0,
					h_align = 4,
					v_align = 3,
					precision = 1,
					bit = 0,
					addends = 0,
				},
			},
		},
	},
}

