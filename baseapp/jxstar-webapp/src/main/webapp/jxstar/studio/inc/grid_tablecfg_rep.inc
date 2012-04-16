	config.eventcfg = {
		
		selGrid: function() {
			var gridCfg = this.grid;
			//��������
			var hdcall = function(grid) {
				//��ʾ����
				JxUtil.delay(500, function(){
					Jxstar.loadInitData(grid);
					
					//ѡ�񴰿ڹر�ʱ�����¼������ñ�����
					grid.on('destroy', function() {
						gridCfg.getStore().reload();
					});
				});
			};
		
			//��ʾ���ݴ���
			var define = Jxstar.findNode('dm_reverse');
			Jxstar.showData({
				pagetype: 'grid',
				filename: define.gridpage,
				width: 500,
				nodedefine: define,
				title: define.nodetitle,
				callback: hdcall
			});
		}, 
		
		commitCfg: function() {
			var records = this.grid.getSelectionModel().getSelections();
			if (!JxUtil.selected(records)) return;
			
			for (var i = 0; i < records.length; i++) {
				var state = records[i].get('dm_tablecfg__state');
				if (state != '0') {
					JxHint.alert(jx.dm.hasnew);	//'ѡ��ļ�¼�д���״̬���ǡ����ɡ��ļ�¼�������ύ��'
					return true;
				}
			}
			
			var self = this;
			var hdcall = function() {
				//ȡѡ���¼������ֵ
				var params = 'funid='+ self.define.nodeid;
				for (var i = 0; i < records.length; i++) {
					params += '&keyid=' + records[i].get(self.define.pkcol);
				}

				//��������Ĳ���
				params += '&pagetype=editgrid&eventcode=commit';

				//ִ�д���������
				var endcall = function(data) {
					//���¼�������
					self.grid.getStore().reload();
				};

				//��������
				Request.postRequest(params, endcall);
			};
			//'�������ɵ�������Ϣ���ύ����ʽ���У�ȷ���ύ��'
			Ext.Msg.confirm(jx.base.hint, jx.dm.backyes, function(btn) {
				if (btn == 'yes') hdcall();
			});
		},
		
		compdm: function() {
			var self = this;
			
			//��ʾSQL���ı���
			var checkForm = new Ext.form.FormPanel({
				border: false,
				frame: false,
				layout:'fit',
				labelAlign: 'top',
				baseCls: 'x-plain',
				items: [{xtype:'textarea', name:'dm_tablecfg__check_sql', border:false, 
						 style:'font-size:12px;border-width:0;line-height:20px;', readOnly:true}]
			});
			
			//������ʾ����SQL�ĶԻ���
			var checkWin = new Ext.Window({
				title:jx.dm.difftitle,	//'���ò������SQL'
				layout:'fit',
				width:500,
				height:500,
				resizable: true,
				modal: true,
				closeAction:'close',
				items:[checkForm],

				buttons: [{
					text:jx.base.commit,	//'�ύ'
					handler:function(){//'��ִ�����ò������SQL��ȷ���ύ��'
						Ext.Msg.confirm(jx.base.hint, jx.dm.exeup, function(btn) {
							if (btn == 'yes') {
								var params1 = 'funid='+ self.define.nodeid;
								params1 += '&pagetype=editgrid&eventcode=commitsql';
								Request.postRequest(params1, null);
								
								checkWin.close();
							}
						});
					}
				},{
					text:jx.base.close,	//'�ر�'
					handler:function(){checkWin.close();}
				}]
			});
			
			var hdcall = function() {
				//ִ�д���������
				var endcall = function(data) {
					checkWin.show();
					var sql = data.sql;
					checkForm.getForm().findField('dm_tablecfg__check_sql').setValue(sql);
				};

				//�������
				var params = 'funid='+ self.define.nodeid + '&pagetype=editgrid&eventcode=compdm';
				//��������
				Request.postRequest(params, endcall);
			};
			//'�Ƚ�����ʽ���е�������Ϣ������Ҫ�Ƚϳ���ʱ�䣬ȷ����ʼ�Ƚ���'
			Ext.Msg.confirm(jx.base.hint, jx.dm.startcfg, function(btn) {
				if (btn == 'yes') hdcall();
			});
		},
		
		compdb: function() {
			var self = this;
			
			//��ʾSQL���ı���
			var checkForm = new Ext.form.FormPanel({
				border: false,
				frame: false,
				layout:'fit',
				labelAlign: 'top',
				baseCls: 'x-plain',
				items: [{xtype:'textarea', name:'dm_tablecfg__check_sql', border:false, 
						 style:'font-size:12px;border-width:0;line-height:20px;', readOnly:true}]
			});
			
			//������ʾ����SQL�ĶԻ���
			var checkWin = new Ext.Window({
				title:jx.dm.difftitle,	//'���ò������SQL'
				layout:'fit',
				width:500,
				height:500,
				resizable: true,
				modal: true,
				closeAction:'close',
				items:[checkForm]
			});
			
			var hdcall = function() {
				//ִ�д���������
				var endcall = function(data) {
					checkWin.show();
					var sql = data.sql;
					checkForm.getForm().findField('dm_tablecfg__check_sql').setValue(sql);
				};

				//�������
				var params = 'funid='+ self.define.nodeid + '&pagetype=editgrid&eventcode=compdb';
				//��������
				Request.postRequest(params, endcall);
			};
			//'���ݿ�ṹ��������Ϣ������Ҫ�Ƚϳ���ʱ�䣬ȷ����ʼ�Ƚ���'
			Ext.Msg.confirm(jx.base.hint, jx.dm.startdb, function(btn) {
				if (btn == 'yes') hdcall();
			});
		}
	};