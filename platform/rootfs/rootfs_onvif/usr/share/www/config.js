//cookie
//声明配置值
var config = {};
//版本号
//全局
config.stage = {};
//开启Debug
//启用js动画
//系统
//定义html地址
//影配置

var sharpen=0;
var hue=0;
var saturation=0;
var brightness=0;
var contrast=0;

var strength=0;
var ae_compensation=0;
var denoise_strength=0;
$(window).ready(function(){
//	alert("窗体加载完毕，开始绑定函数");
	//预热舞台
	readyStage();
	//重载舞台
	stageResize();
//  resize();
   resizeM();
   setHandover();
   // deviceName_load();
	//插件启动
	var ip=document.location.host;
	var port=document.location.port;
	if(port=="")	//80
	{
	port=80;
	}
	else{
	var i=document.location.host.indexOf(":");
	ip=document.location.host.substring(0,i);
	}

	//开启本地时间
	setTimeout("renewtime()",10);
	$(".m_date").datepicker({
	     showButtonPanel: true
    });
	
	$('.in').each(function(index){
			$(this).focusout(function() {
				if($(this).val() == ''){
					alert('输入不能为空');
					}
			});
			$(this).focus(function(){
				$(this).val('');
			});
			$(this).keyup(function(){
				var str = $(this).val();
				if(index == 0){
					if(str.length == 1){
						if(str > 2){
							$(this).val('2');	
						}	
					}
					else{
						if(str.slice(0,1) == '2'){
							if(str.slice(1,2) > 4){
								$(this).val(str.slice(0,1)+'3');
							}
						}
					}
				}
				else{
					if(str.length == 1){
						if(str > 6){
							$(this).val('5');
						}	
					}	
				}
				if($(this).val().length == 2){
					$('.in').eq(index + 1).focus();	
				}
		});	
	});	
	$('.mask_ipcam').css('padding-top',$('.mask_ipcam').height()/2-60+'px');
//	$('#xp0').click(function(){
////		alert("fdfdfdf");
//		//DHiMPlayer.FullScreen(bFullScreen = !bFullScreen);
//   	fullscreen_func();
//	});
	// $('#cl a').each(function(index){
		// $(this).click(function(){
			// streamchange(index);
		// });
	// });
	$('#lum_pa').click(function(){
		
		var value_1=document.getElementById('juan_envload#color@lum').value;
		slider_lum.f_setValue((parseInt(value_1,10)-1),0);
		image_preview_content('sl0slider');
	});
	$('#lum_pl').click(function(){
		
		var value_1=document.getElementById('juan_envload#color@lum').value;
		slider_lum.f_setValue((parseInt(value_1,10)+1),0);
		image_preview_content('sl0slider');
	});
	$('#con_pa').click(function(){
		
		var value_2=document.getElementById('juan_envload#color@con').value;
		slider_con.f_setValue((parseInt(value_2,10)-1),0);
		image_preview_content('sl1slider');
	});
	$('#con_pl').click(function(){
		
		var value_2=document.getElementById('juan_envload#color@con').value;
		slider_con.f_setValue((parseInt(value_2,10)+1),0);
		image_preview_content('sl1slider');
	});
	$('#sat_pa').click(function(){
		
		var value_3=document.getElementById('juan_envload#color@sat').value;
		slider_sat.f_setValue((parseInt(value_3,10)-1),0);
		image_preview_content('sl2slider');
	});
	$('#sat_pl').click(function(){
		
		var value_3=document.getElementById('juan_envload#color@sat').value;
		slider_sat.f_setValue((parseInt(value_3,10)+1),0);
		image_preview_content('sl2slider');
	});
	$('#hue_pa').click(function(){
		
		var value_4=document.getElementById('juan_envload#color@hue').value;
		slider_hue.f_setValue((parseInt(value_4,10)-1),0);
		image_preview_content('sl3slider');
	});
	$('#hue_pl').click(function(){
		
		var value_4=document.getElementById('juan_envload#color@hue').value;
		slider_hue.f_setValue((parseInt(value_4,10)+1),0);
		image_preview_content('sl3slider');
	});
//	$('#shar_pa').click(function(){
//		
//		var value_5=document.getElementById('isp@sharpness').value;
//		slider_sha.f_setValue((parseInt(value_5,10)-1),0);
//		image_preview_content('sl0slider');
//	});
//	$('#shar_pl').click(function(){
//		
//		var value_5=document.getElementById('isp@sharpness').value;
//		slider_sha.f_setValue((parseInt(value_5,10)+1),0);
//	});
}).resize(function(){
	stageResize();
//  resize();
    resizeM();
    setHandover();
    // deviceName_load();
});
var g_Radio=1.25;//1.78
function  ChangeRadio() {
    if(g_Radio==1.25)
    {
        g_Radio=1.78;            
    }
    else
    {
        g_Radio=1.25;
    }
    resizeM();
    
    
}
function resizeM(){
         var mbbw;
	var mbbh;
	var wwidth =document.documentElement.clientWidth;
	var wheight=document.documentElement.clientHeight;
	if (wheight<600) wheight=600;
	//ma31,dra24,mc13,pb26

	mbbh=wheight-$('#ma').height()-$('#dra').height()-$('#mc').height()-$('#pb').height()-5-10;
	
	glhight=wheight-$('#ma').height()-$('#dra').height()-$('#mc').height()+5-10;
	//mcup:349
	grhight=wheight-349-$('#ma').height()-$('#dra').height()-$('#mc').height()+98;
	
	mbbw=mbbh *64/51;
	mbbw=mbbh *g_Radio;
	
	$('#mb').css('width', mbbw+(145*2+8));
	$('#mbb').css('width', mbbw);//yzt 0508
	$('#mbb').css('height', mbbh);	
	$('#mbal').css('height', glhight);
	$('#yt3').css('height', grhight);
	$('#st').css('width', mbbw);
	$('#backGround').css('height', wheight);	
	$('#dcl').css('height', glhight);
	$('#QS').css('left', screen.width-170);
	return;
	if(screen.width<$('#mbc').height()+170)
	{
	   $('#QS').css('left', $('#mbc').height()+10);
	}
	if(g_Radio==1.78)
	{
	   $('#QS').setStyle('left', screen.width-100);
	   $('QS').style.display='none';
	}else
	{
	   if(g_bQS&&!g_bClose)
	   {
	     $('QS').style.display='';
	   }
	   
	}
 	$('QS').setStyle('top', screen.height-550);
	 if (window.ActiveXObject) {
                                 var ua = navigator.userAgent.toLowerCase();
                                var ie=ua.match(/msie ([\d.]+)/)[1]
                               	if(ie==6.0){
				    
                                    position_fixed(document.getElementById("QS"),wwidth-150,wheight-150);
				     if(screen.width-wwidth>60)
				     {
					$('QS').style.display='none';
				     }else
				     {
					if(g_Radio==1.78)
					{
					   $('QS').style.display='none';
					}else
					{
					   if(g_bQS&&!g_bClose)
					   {
					       $('QS').style.display='';
					   }
					}
				     }
                                    }
                                }
	
}
//舞台自适应
/*function stageResize(){
	$('#ipcam_display,.mask_ipcam,#JaViewer_view').height($(window).height()-186);
	$('.window-preview').height($(window).height()-150).width($(window).width() - 436).css('top','98px');
	if($('.window-preview').height() < 447){
		$('.window-preview').height(447);
		$('#ipcam_display,.mask_ipcam,#JaViewer_view').height(422);
	}
	if($('.window-preview').width() < 600){
		$('.window-preview').width(600)
		}

};*/
function stageResize(){
	var W=$(window).innerWidth()<960?960:$(window).width();
	var H=$(window).innerHeight()<560?560:$(window).height();
	//alert(W+' '+H);
	//alert('mbb:'+$('#mbb').width()+' '+$('#mbb').height());
	//$('#ipcam_display,.mask_ipcam,#JaViewer_view').height(540).width(960);
    // $('#wrap').width(W*0.9).height(H);
    // $('#stage').width($('#wrap').width());
     $('#ipcam_display,.mask_ipcam,#JaViewer_view').width('100%');
     $('#ipcam_display,.mask_ipcam,#JaViewer_view').height('100%');
    // $('#area-stage-right').width($('#stage').width()-$('#left')).css('right',$('#left'));
     //$('#area-stage-right').height(H-100);
    // $('.mainer').height($('.window').height()-60)
	/*$('#ipcam_display,.mask_ipcam,#JaViewer_view').height($(window).height()-206).width($(window).width() - 456);
	if($('.window-preview').height() < 447){
		$('#ipcam_display,.mask_ipcam,#JaViewer_view').height(422);
	}
	if($('.window-preview').width() < 600){
		$('#ipcam_display,.mask_ipcam,#JaViewer_view').width(600);
		}*/
};

 
   	  
 
//预热舞台
function readyStage(){
	//预览/配置标签
	//$('#logo-config').children('span').eq(0).css({"width":"100px","height":"52px","line-height":"52px","margin-top":"3px","color":"#666666","font-size":"26px","border-bottom":"0"});			
//	$('.logo-inactive').click(function(){
//		$('#logo-config').children().css({"width":"58px","height":"40px","line-height":"40px","margin-top":"15px","color":"#ccc","font-size":"20px","border-bottom":"1px solid #CCC"});
//		$(this).css({"width":"100px","height":"52px","margin-top":"3px","color":"#666666","font-size":"26px","border-bottom":"0"});
//	});
	//切换次级菜单
	$('li.btn-left').click(function(e){
		var btn = $(this);
		var currentid = btn.attr("id");
		//获取链接
		$('li.btn-left-active').removeClass('btn-left-active')
		btn.addClass('btn-left-active');
//		showInfo('bingo!');
		//特殊标签
		$('.btn-left').children('ul').hide();
		$(this).find('ul').show();
//		hideInfo();
	//	bindAction();
	});
	$('li.btn-left').mouseenter(function(e){
		var btn = $(this);
		$(this).find('ul').show();
//		hideInfo();
	//	bindAction();
	});
	$('li.btn-left').mouseleave(function(e){
		$(this).find('ul').hide();
//		hideInfo();
	//	bindAction();
	});
	//对应窗体显示
	$('.record_ul li').click(function(){
		var dest = $(this);
		$(".record_ul li").removeClass('submenu_current1');
		dest.addClass('submenu_current1');
	})
	$('.mainMenu').click(function(){
		var dest = $(this);
		var destmark = dest.attr("id");
		$("ul li").removeClass('submenu_current');
		dest.parent().addClass('submenu_current');
		$('#area-stage-right').children('div').addClass('hidden');
		$("."+destmark).removeClass('hidden');
		if(destmark == "video")
		{
			encode_load_content();
		}
		else if(destmark == "image")
		{
			image_load_content();
		}
		else if(destmark == "local-network")
		{
			local_load_content();
		}
		else if(destmark == "remote-network")
		{
			remote_load_content();
		}
		else if(destmark == "danale")
		{
			danale_load_content();
		}
		else if(destmark == "time")
		{
			time_zone_load();
		}
		else if(destmark == "devinfo")
		{
			devinfo_load_content(true);
		}
		else if(destmark == "user-management")
		{
			user_management_load_content();
		}
		else if(destmark =="record")
		{
			//record_load_content();
		}
		else if(destmark == "playback")
		{
			playback_load_content();
		}
		else if(destmark =="isp")
		{
			isp_load_content();
		}
		else if(destmark =="audio")
		{
			audio_load_content();
		}
		else if(destmark =="cover")
		{
			cover_load_content();
		}
		else if(destmark =="overlay")
		{ 
			overlay_load_content();
		}
		else if(destmark =="wireless")
		{ 
			wireless_load_content();
		}
	});
	//表格上色&排版
	$(".table-common").find("tr:even").children('td').css("background-color","#F1F1F1");
	$(".marker").css("padding-left","5px");
	//CAM HOVER
	$('#ptz-controller-cam').hover(function(){$(this).css("background-image","url(images1/ptz-controller-cam-hover.png)");},function(){$(this).css("background-image","url(images1/ptz-controller-cam.png)");});
//	//PTZ EXPANSION
//	$('#consoler').mouseenter(function()
//	{
//		$('#ptz-controller-up').stop(true,true).css({"opacity":0 , "top":"48px"}).animate({"opacity":1 , "top":"10px"},200);
//		$('#ptz-controller-left').stop(true,true).css({"opacity":0 , "left":"48px"}).animate({"opacity":1 , "left":"10px"},200);
//		$('#ptz-controller-right').stop(true,true).css({"opacity":0 , "left":"48px"}).animate({"opacity":1 , "left":"102px"},200);
//		$('#ptz-controller-down').stop(true,true).css({"opacity":0 , "top":"48px"}).animate({"opacity":1 , "top":"102px"},200);
//	});
//	//PTZ PACK
//	$('#consoler').mouseleave(function()
//	{
//		$('#ptz-controller-up').animate({"opacity":0 , "top":"-48px"},200,function(){$(this).css({"top":"48px"});});	
//		$('#ptz-controller-left').animate({"opacity":0 , "left":"-48px"},200,function(){$(this).css({"left":"48px"});});	
//		$('#ptz-controller-right').animate({"opacity":0 , "left":"144px"},200,function(){$(this).css({"left":"48px"});});	
//		$('#ptz-controller-down').animate({"opacity":0 , "top":"144px"},200,function(){$(this).css({"top":"48px"});});	
//	});
//	//PTZ ARROW HOVER
//	$('#ptz-controller-up').hover(function(){$(this).css("background-image","url(images1/ptz-controller-up-hover.png)");},function(){$(this).css("background-image","url(images1/ptz-controller-up.png)");});
//	$('#ptz-controller-left').hover(function(){$(this).css("background-image","url(images1/ptz-controller-left-hover.png)");},function(){$(this).css("background-image","url(images1/ptz-controller-left.png)");});
//	$('#ptz-controller-right').hover(function(){$(this).css("background-image","url(images1/ptz-controller-right-hover.png)");},function(){$(this).css("background-image","url(images1/ptz-controller-right.png)");});
//	$('#ptz-controller-down').hover(function(){$(this).css("background-image","url(images1/ptz-controller-down-hover.png)");},function(){$(this).css("background-image","url(images1/ptz-controller-down.png)");});
//	
//	//Zoom in/out
//	$('#zoom-in').hover(function(){$(this).css("background-image","url(images1/zoom-in-hover.png)");},function(){$(this).css("background-image","url(images1/zoom-in.png)");});
//	$('#zoom-out').hover(function(){$(this).css("background-image","url(images1/zoom-out-hover.png)");},function(){$(this).css("background-image","url(images1/zoom-out.png)");});

	//Others
	/*$(".w_imagebtn").eq(0).hover(function(){$(this).css("background-image","url(images/record-hover.png)");},function(){$(this).css("background-image","url(images/record.png)");});
	$(".w_imagebtn").eq(1).hover(function(){$(this).css("background-image","url(images/playback-hover.png)");},function(){$(this).css("background-image","url(images/playback.png)");});*/
	$(".w_imagebtn").eq(0).hover(function(){$(this).css("background-image","url(images/stream-change-hover.png)");},function(){$(this).css("background-image","url(images/stream-change.png)");});
	$(".w_imagebtn").eq(1).hover(function(){$(this).css("background-image","url(images/stream-change-hover.png)");},function(){$(this).css("background-image","url(images/stream-change.png)");});
	$(".w_imagebtn").eq(2).hover(function(){$(this).css("background-image","url(images/stream-change-hover.png)");},function(){$(this).css("background-image","url(images/stream-change.png)");});
	$(".w_imagebtn").eq(3).hover(function(){$(this).css("background-image","url(images/stream-change-hover.png)");},function(){$(this).css("background-image","url(images/stream-change.png)");});

	var url = self.location.href.match(/\=.*/);
};

//绑定动作
function bindAction(){	
	//选择框动作	
		//判断是否是默认值		
		//点击动作		
			//切换状态
			$(this).parent().toggleClass('changed');
			//更改标题栏		
};


//获取一个随机数值
function setMid() {
	//获取暂存索引
	var mid = Math.random().toString().replace(/\./, '');
	//返回数值
	return mid;
};

//将Json转化为字符串
function parseString(para){
	var mimikoString = JSON && typeof(para) != 'string' ? JSON.stringify(para) : para;
	return mimikoString;
};

//将一个字符串转换为Json
function parseJson(para){
	var mimikoJson = typeof(para) != 'object' ? $.parseJSON(para) : para;
	return mimikoJson;
};

//显示信息
function showInfo(para, callback){
	if(!$('#txtLoadinInfo').length){
		$('#message_here').append('<span id="txtLoadinInfo">' + para +'</span>');
	}else
	{
		$('#txtLoadinInfo')[0].innerText = para;
	};
	$('#txtLoadinInfo').stop(false, true).css({
		opacity:0
	}).animate({
		opacity:1
	},250, function(){
		if ($.isFunction(callback)) {
			callback();
		};
	});
};

//隐藏信息
function hideInfo(para){
	window.setTimeout(function(){
		$('#txtLoadinInfo').stop(false, true).animate({
			opacity:0
		}, 250, function(){
			$(this).remove();
		});
	}, para);
};

//Azrael的试管
//本地时间函数
var yy,mm,dd,hh,mi,ss;
var init_set_time = false
function renewtime()
{
    var myDate = new Date();
	yy=myDate.getFullYear().toString();
	if (yy.length<4)
	{
		var i = 4-yy.length;
		for (var j = 0; j < i; j++)
		{
			yy = "0" + yy;
		}
	}
	mm=(myDate.getMonth()+parseInt(1)).toString();
	mm=(mm.length==1)?("0"+mm):mm
	dd=myDate.getDate().toString();
	dd=(dd.length==1)?("0"+dd):dd
	hh=myDate.getHours().toString();
	hh=(hh.length==1)?("0"+hh):hh
	mi=myDate.getMinutes().toString();
	mi=(mi.length==1)?("0"+mi):mi
	ss=myDate.getSeconds().toString();
	ss=(ss.length==1)?("0"+ss):ss
	// if (location.path=="/view.html") {
		$('#time_pc')[0].value = yy + "-" + mm + "-" + dd + "  " + hh + ":" + mi + ":" + ss;		
	// };
	
	setTimeout("renewtime()",100);
	if(!init_set_time){
		$('.m_date').val(yy + "-" + mm + "-" + dd);
		$('.in').eq(0).val(hh).end().eq(1).val(mi).end().eq(2).val(ss);
		init_set_time = true;
	}
}
//主次码流预览标签
var stream_state = 0;
function preview_stream(index)
{
	    switch(index){
	    case 0:
	    $('.window-preview1').children('.title-window')[0].innerHTML = langstr.main_stream;
		stream_state = 0;
		streamchange(stream_state);
		break;
		case 1:
		$('.window-preview1').children('.title-window')[0].innerHTML = langstr.sub_stream;
		stream_state = 1;
		streamchange(stream_state);
		break;
		default:
		$('.window-preview1').children('.title-window')[0].innerHTML = langstr.main_stream;
		stream_state = 0;
		streamchange(stream_state);
		break;
	     }
		
	
		
	
}
function pic_btn_down()
{
	location.href = "playback.html";
}
//音频开关
var Switch = true;
function AudioSwitch()
{
	if (Switch == true)
	{
		$('#Audio').removeClass($('#Audio').className);
		$('#Audio').addClass('p10');
		Switch = false;
		audiochange(Switch);
	}else if (Switch == false)
	{
		$('#Audio').removeClass($('#Audio').className);
		$('#Audio').addClass('p102');
		Switch = true;
		audiochange(Switch);
	}
}
//snapshot
function Snapshot()
{
	var url = "http://" + g_ip + ":" + g_port + "/snapshot.jpg?size=-1x-1&download=yes";
	window.open(url);
}

//升级界面动画
function showBg()
{  
//	var bh = $("body").height();  
//	var bw = $("body").width();  
//	$("#maskbg").css({ height:bh, width:bw, display:"block" });  
	$("#maskbg").fadeIn(200);
	$("#update_process").fadeIn(400);  
}   
function closeBg() {  
	$("#maskbg,#update_process").fadeOut();  
}  
//颜色配置/其他设置
function setHandover(){
	$('#taba1').click(function(){
//		new Event(e).stop();
//		if ($('#taba1').hasClass('t3'))
//		{
//			$('#taba1').removeClass($('#taba1').className);
//			$('#taba1').addClass('t1');			
//			$('#taba2').removeClass($('#taba2').className);
//			$('#taba2').addClass('t2');
			$('#yt3t1').css("display", "block");		
			$('#yt3t2').css("display", "none");			
//		}
});
$('#taba2').click(function(){
//		new Event(e).stop();
//		if ($('#taba2').hasClass('t2'))
//		{
//			$('#taba1').removeClass($('#taba2').className);
//			$('#taba1').addClass('t3');			
//			$('#taba2').removeClass(this.className);
//			$('#taba2').addClass('t4');
			$('#yt3t1').css("display", "none");		
			$('#yt3t2').css("display", "block");			
//		}
});
}
//预览配置切换函数
function cslshine(tips)
{
	
	var DHiMPlayer_image = document.getElementById('DHiMPlayer_image');
	var DHiMPlayer = document.getElementById('DHiMPlayer');
	switch(tips)
	{
		case 0: 
			$('#mb').show(); 
			$('#area-stage-left').hide();
			$('#area-stage-right').hide();
			$('#area-stage-help').hide();
             $('#stage').hide(); 
            $('#settings').hide(); 
			$('#mc').show();
			$('#huifang').hide(); 
			$('.window-preview').show();
			//--
			$('#logo-config span:eq(0)').addClass('logo-inactive');
		   $('#logo-config span:eq(1)').removeClass('logo-inactive');
		   stageResize();
		   //--
			if(stream_state==0){
				setTimeout("flash_video(\"JaViewer_view\", \"720p.264\")", 1000);
			}else if(stream_state == 1){
				setTimeout("flash_video(\"JaViewer_view\", \"360p.264\")", 1000);
			}else{
				setTimeout("flash_video(\"JaViewer_view\", \"720p.264\")", 1000);
			}
			if(DHiMPlayer_image){
				DHiMPlayer_image.close();
			}
			if(DHiMPlayer){
				DHiMPlayer.OpenByIP(g_ip,g_port);
				DHiMPlayer.UserLogon(g_usr,g_pwd);
				DHiMPlayer.OpenChannel(0,stream_state);
			}
			load1();
			break;
		case 1: 
		//--
			if(DHiMPlayer){
				DHiMPlayer.close();
			}
			//--
			/*if(DHiMPlayer_image){
				DHiMPlayer_image.OpenByIP(g_ip,g_port);
				DHiMPlayer_image.UserLogon(g_usr,g_pwd);
				DHiMPlayer_image.OpenChannel(0,1);
			}*/
          //--
			$('#logo-config span:eq(1)').addClass('logo-inactive');
		   $('#logo-config span:eq(0)').removeClass('logo-inactive');
		   //--
//		   stageResize();
			encode_load_content();
			$('#mb').hide(); 
			$('#area-stage-left').show();
			$('#area-stage-right').show();
			$('#area-stage-help').show();
             $('#stage').show(); 
            $('#settings').hide(); 
			$('#mc').hide();
			$('#huifang').hide(); 

			//--
			$('.window-preview').hide();
			$('#area-stage-right').show();
			$('#area-stage-help').show();
				$('a.btn-left-active').removeClass('btn-left-active')
				$("#video-image").addClass('btn-left-active');
				$('#area-stage-left').children('span').addClass('hidden');
				$(".video-image").removeClass('hidden');
				$("ul li").removeClass('submenu_current');
				$("#video").parent().addClass('submenu_current');
				setTimeout("$('#area-stage-right').children('div').addClass('hidden');$('.video').removeClass('hidden');",50);	
				setTimeout("video_preload_content()",55);		
				//--	
			break;
		case 2: 
			if(DHiMPlayer){
				DHiMPlayer.close();
			}
			$('#logo-config').children().css({"width":"58px","height":"40px","line-height":"40px","margin-top":"15px","color":"#ccc","font-size":"20px","border-bottom":"1px solid #CCC"});
			$('#logo-inactive1').css({"width":"100px","height":"52px","margin-top":"3px","color":"#666666","font-size":"26px","border-bottom":"0"});
			$('#mb').hide(); 
			$('#mc').hide();
			$('#settings').show();

			//--
			$('.window-preview').hide();
			$('#area-stage-right').show();
			$('#area-stage-help').show();
				$('a.btn-left-active').removeClass('btn-left-active')
				$("#advanced").addClass('btn-left-active');
				$('#area-stage-left').children('span').addClass('hidden');
				$(".advanced").removeClass('hidden');
				$("ul li").removeClass('submenu_current');
				$("#playback").parent().addClass('submenu_current');
				setTimeout("$('#area-stage-right').children('div').addClass('hidden');$('.playback').removeClass('hidden');",50);	
				setTimeout("playback_load_content()",55);			
				//--
			break;
			case 3:
			$('#mb').hide(); 
			$('#area-stage-left').hide();
			$('#area-stage-right').hide();
			$('#area-stage-help').hide();
             $('#stage').hide(); 
//          $('#settings').show(); 
			$('#mc').hide();
			$('#huifang').show();
			break;
		default: 
			$('#mb').show(); 
			$('#mc').show();
			$('#area-stage-left').hide();
			$('#area-stage-right').hide();
			$('#area-stage-help').hide();
             $('#stage').hide(); 
            $('#huifang').hide(); 
             //
			$('.window-preview').show();
			$('#logo-config span:eq(0)').addClass('logo-inactive');
		   $('#logo-config span:eq(1)').removeClass('logo-inactive');
           //--
		   stageResize();
			if(stream_state==0){
				setTimeout("flash_video(\"JaViewer_view\", \"720p.264\")", 1000);
			}else if(stream_state == 1){
				setTimeout("flash_video(\"JaViewer_view\", \"360p.264\")", 1000);
			}else{
				setTimeout("flash_video(\"JaViewer_view\", \"720p.264\")", 1000);
			}
			if(DHiMPlayer_image){
				DHiMPlayer_image.close();
			}
			if(DHiMPlayer){
				DHiMPlayer.OpenByIP(g_ip,g_port);
				DHiMPlayer.UserLogon(g_usr,g_pwd);
				DHiMPlayer.OpenChannel(0,stream_state);
			}
	}
}
