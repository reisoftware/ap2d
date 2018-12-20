entry {
	book = {
		name = [[3in1]],
		sheets = {
			{
				name = [[partlist-]],
				cell_ws = {
					{
						col = [[a]],
						size = 20,
					},
					{
						col = [[d]],
						size = 10,
					},
					{
						col = [[h]],
						size = 10,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 20,
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
								content = [[part]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[SECTION]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[MAT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[NAME]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						filter_rule = [[filter_pass_bolt();]],
						group_rule = [[group_by_part_no_section_length();]],
						sort_rule = [[sort_by_part_no_section_length();]],
						cells = {
							{
								content = [[part]],
								content_rule = [[content_by_part_no();]],
								style = [[cs_part_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								h = 20,
								content = [[SECTION]],
								content_rule = [[content_by_section();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								h = 20,
								content = [[MAT]],
								content_rule = [[content_by_mat();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[content_by_length();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[content_by_weight();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[NAME]],
								content_rule = [[content_by_name();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						filter_rule = [[filter_pass_bolt();]],
						group_rule = [[equ();]],
						cells = {
							{
								h = 20,
								content = [[Total]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count_sum();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+3);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
						},
					},
				},
			},
			{
				name = [[assemblylist-]],
				cell_ws = {
					{
						col = [[a]],
						size = 20,
					},
					{
						col = [[d]],
						size = 10,
					},
					{
						col = [[h]],
						size = 10,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 20,
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
								content = [[assembly]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[SECTION]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[MAT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						init_rule = [[add_assembly();]],
						filter_rule = [[filter_pass_bolt();]],
						group_rule = [[group_by_no_section_length();]],
						sort_rule = [[sort_by_no_section_length();]],
						cells = {
							{
								h = 20,
								content = [[assembly]],
								content_rule = [[content_by_no();]],
								style = [[cs_assembly_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[SECTION]],
								content_rule = [[content_by_section();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[MAT]],
								content_rule = [[content_by_mat();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[content_by_length();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[content_by_weight();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						init_rule = [[add_assembly();]],
						filter_rule = [[filter_pass_bolt();]],
						group_rule = [[equ();]],
						cells = {
							{
								h = 20,
								content = [[Total]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count_sum();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+3);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
						},
					},
				},
			},
			{
				name = [[assembly-part_list-]],
				cell_ws = {
					{
						col = [[a]],
						size = 20,
					},
					{
						col = [[d]],
						size = 10,
					},
					{
						col = [[h]],
						size = 10,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 20,
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
								h = 20,
								content = [[assembly-part]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[SECTION]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[MAT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
						},
					},
					{
						type = 2,
						init_rule = [[add_all();]],
						filter_rule = [[filter_pass_bolt();]],
						group_rule = [[group_by_no();]],
						sort_rule = [[sort_by_no();]],
						tables = {
							{
								type = 1,
								border = 1,
								init_rule = [[add_part_by_super_no();]],
								filter_rule = [[]],
								group_rule = [[equ();]],
								sort_rule = [[]],
								cells = {
									{
										h = 20,
										content = [[assembly-part]],
										content_rule = [[content_by_no();]],
										style = [[cs_part_text]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[COUNT]],
										content_rule = [[content_by_count();]],
										style = [[cs_int]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
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
								init_rule = [[add_part_by_super_no();]],
								group_rule = [[group_by_part_no_section_length();]],
								sort_rule = [[sort_by_part_no_section_length();]],
								cells = {
									{
										h = 20,
										content = [[assembly-part]],
										content_rule = [[content_by_part_no();]],
										style = [[cs_assembly_text]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[SECTION]],
										content_rule = [[content_by_section();]],
										style = [[cs_assembly_text]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[MAT]],
										content_rule = [[content_by_mat();]],
										style = [[cs_assembly_text]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[COUNT]],
										content_rule = [[content_by_count();]],
										style = [[cs_int]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[LENGTH(mm)]],
										content_rule = [[content_by_length();]],
										style = [[cs_float]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[LSUM(mm)]],
										content_rule = [[content_by_length_sum();]],
										style = [[cs_float]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[WEIGHT(kg)]],
										content_rule = [[content_by_weight();]],
										style = [[cs_float]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[WSUM(kg)]],
										content_rule = [[content_by_weight_sum();]],
										style = [[cs_float]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
								},
							},
						},
					},
				},
			},
			{
				name = [[boltlist-]],
				cell_ws = {
					{
						col = [[a]],
						size = 20,
					},
					{
						col = [[d]],
						size = 10,
					},
					{
						col = [[h]],
						size = 10,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 20,
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
								content = [[part]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[SECTION]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[MAT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						filter_rule = [[filter_unpass_bolt();]],
						group_rule = [[group_by_part_no_section_length();]],
						sort_rule = [[sort_by_part_no_section_length();]],
						cells = {
							{
								content = [[part]],
								content_rule = [[content_by_part_no();]],
								style = [[cs_part_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								h = 20,
								content = [[SECTION]],
								content_rule = [[content_by_section();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								h = 20,
								content = [[MAT]],
								content_rule = [[content_by_mat();]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LENGTH(mm)]],
								content_rule = [[content_by_length();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WEIGHT(kg)]],
								content_rule = [[content_by_weight();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+1);
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
						filter_rule = [[filter_unpass_bolt();]],
						group_rule = [[equ();]],
						cells = {
							{
								h = 20,
								content = [[Total]],
								style = [[cs_text]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_last_y()+1);
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[COUNT]],
								content_rule = [[content_by_count_sum();]],
								style = [[cs_int]],
								pos_rule = [[
									set_cell_x(get_last_x()+3);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[LSUM(mm)]],
								content_rule = [[content_by_length_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content = [[WSUM(kg)]],
								content_rule = [[content_by_weight_sum();]],
								style = [[cs_float]],
								pos_rule = [[
									set_cell_x(get_last_x()+2);
									set_cell_y(get_last_y());
									set_cell_w(1);
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
					type = 0,
					name = [[cs_text]],
					font = [[Arial]],
					text_color = 1,
					back_color = 37,
					size = 10,
					blod = 0,
					italic = 0,
					h_allign = 3,
					v_allign = 2,
				},
				{
					type = 0,
					name = [[cs_assembly_text]],
					font = [[Arial]],
					text_color = 3,
					back_color = 35,
					size = 10,
					blod = 0,
					italic = 0,
					h_allign = 3,
					v_allign = 2,
				},
				{
					type = 0,
					name = [[cs_part_text]],
					font = [[Arial]],
					text_color = 3,
					back_color = 36,
					size = 10,
					blod = 0,
					italic = 0,
					h_allign = 3,
					v_allign = 2,
				},
				{
					type = 1,
					name = [[cs_int]],
					font = [[Arial]],
					text_color = 5,
					back_color = 0,
					size = 10,
					blod = 1,
					italic = 0,
					h_allign = 1,
					v_allign = 2,
					precision = 1,
					bit = 0,
					addends = 0,
				},
				{
					type = 1,
					name = [[cs_float]],
					font = [[Arial]],
					text_color = 55,
					back_color = 0,
					size = 10,
					blod = 0,
					italic = 1,
					h_align = 4,
					v_align = 2,
					precision = 0.05,
					bit = 2,
					addends = 1,
				},
			},
		},
	},
}

