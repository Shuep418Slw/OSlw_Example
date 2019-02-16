<!doctype html>
<?php
$div=$_GET['D'];
$len=$_GET['L']
?>
<html>
<head>
<meta charset="utf-8">
<title>无标题文档</title>
</head>

<body>
<table width="100%" border="1">
  <tbody>
    <tr>
      <td width="51%" rowspan="2"><canvas id="canvas" width="700" height="700"></canvas></td>
      <td width="49%" height="259"><p>
        <input type="button" name="button" id="button" onClick="butCallBack1();" value="清除">
      </p>
      <p>
        <input type="button" name="button2" id="button2" onClick="butCallBack2();" value="生成">
      </p></td>
    </tr>
    <tr>
      <td><textarea name="textarea" id="textarea"></textarea></td>
    </tr>
  </tbody>
</table>
<script>
	
	var c=document.getElementById("canvas");
	var ctx=c.getContext("2d");
	var g_div=<?php echo($div)?>;
	var global_arr=new Array();
	var down_flag=0;
	var g_x_d=0;
	var g_y_d=0;
	var linew=<?php echo($len)?>;
	function CanvasReset(c2d,div)
	{
		var ctx=c2d.getContext("2d");
		var xd=c2d.width/div
		var yd=c2d.height/div
		g_x_d=xd
		g_y_d=yd
		ctx.clearRect(0,0,c2d.width,c2d.height)
		for(var i=0;i<div+1;i++){
			ctx.moveTo(0,i*yd);
			ctx.lineTo(c2d.width,i*yd);
			
		}
		for(var i=0;i<div+1;i++){
			ctx.moveTo(i*xd,0);
			ctx.lineTo(i*xd,c.height);
			//ctx.stroke();	
		}
		ctx.stroke();	
		
       for(var i=0;i<g_div;i++){          //一维长度为5
          global_arr[i]=new Array(g_div);    //在声明二维
          for(var j=0;j<g_div;j++){      //二维长度为5
             global_arr[i][j]=0;
       		}
	 }
		
	}
	CanvasReset(c,g_div)
	


	c.onmousedown=function(event) {		
		//alert(xy)
		down_flag=1;
	}
	c.onmousemove=function(event) {
    	if(down_flag){
			var xy=getMousePos(c,event);		
			var id_x=Math.floor(xy[0]/g_x_d)
			var id_y=Math.floor(xy[1]/g_y_d)
			var ctx=c.getContext("2d");
			ctx.fillRect(id_x*g_x_d,id_y*g_y_d,g_x_d*linew,g_y_d*linew)
			
			for(var i=0;i<linew;i++)
				for(var j=0;j<linew;j++)
					global_arr[id_y+i][id_x+j]=1;
			
			ctx.stroke();
		}
	}
	
	c.onmouseout=function(e){
		down_flag=0;
	}
	
	c.onmouseup=function(e){
		down_flag=0;
	}
	
	function getMousePos(canvas, event) {
		//1
		var rect = canvas.getBoundingClientRect();
		//2
		var x = event.clientX - rect.left * (canvas.width / rect.width);
		var y = event.clientY - rect.top * (canvas.height / rect.height);
		return[x,y];
	}

	function arr2int(arr,len){
		var l1=arr.length
		var re=new Array(l1)
		for(var i=0;i<l1;i++){
			var temp=0;
			for(var j=0;j<len;j++){
				temp+=(arr[i][j]<<(j))
			}
			re[i]=temp;
		}
		return re		
	}
	function butCallBack1(){
	var ele = document.getElementById("textarea");
	ele.value = ""
	CanvasReset(c,g_div)
	}

	function butCallBack2(){
	var ele = document.getElementById("textarea");
	ele.value = arr2int(global_arr,g_div)
	//alert(arr2int(global_arr,g_div));
	}
</script>
</body>
</html>
