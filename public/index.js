
// Put all onload AJAX calls here, and event listeners


var names=[];

jQuery(document).ready(function() {

    // On page-load AJAX Example
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/foldercontents',   //The server endpoint we are connecting to
        data: {
            
        },
        success: function (data) {
            console.log(data);
            /*  Do something with returned object
            Note that what we get is an object, not a string, 
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
            */
 
           data.forEach((element) => {
              
               
               if(element.name.includes('.svg')){             
                   names.push(element);
                }
            }); 
            $("#imgSi").attr('src', 'uploads/' + names[0].name)
            let file = names[0];
            let $titdesc = $(
                `
                <tr class='clear width'>
                <td><label>Title  :</label></td>
                <td class='width'>
                <input type="text" name="title" value="${file.title}" placeholder="Enter Title"></td>
                </tr>
                <tr class='clear width'>
                <td class='clear'><label>Description  :</label></td>
                <td name="desc" class='width'>
                <input type="text" name="desc" value="${file.desc}" placeholder="Enter Title"></td>
                <td><input type="submit" name="btn" value="Submit"></td>    
                </tr>
                `
            )
            $titdesc.appendTo($('#Titledescription'))
            file.rectList.forEach((rect,index)=>{
                let $RectFile =$(
                        `<tr class="clear">
                            <td>Rectangle ${index + 1}
                            </td>
                            <td>Upper left corner: x :${rect.x}${rect.units} , y:${rect.y}${rect.units},<br/>
                                width: ${rect.w}${rect.units} , height: ${rect.h}${rect.units} 
                            </td>
                            <td> ${rect.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $RectFile.appendTo($("#properties"))
    
            });
    
            file.circList.forEach((circ,index)=>{
                let $CircFile =$(
                        `<tr class="clear">
                            <td>Circle ${index + 1}
                            </td>
                            <td>Centre: x :${circ.cx}${circ.units} , y:${circ.cy}${circ.units},<br/>
                                radius: ${circ.r}${circ.units} 
                            </td>
                            <td> ${circ.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $CircFile.appendTo($("#properties"))
    
            });
            

            file.pathList.forEach((path,index)=>{
                let $PathFile =$(
                        `<tr class="clear">
                            <td>Path ${index +1}
                            </td>
                            <td> d :${path.d}
                            </td>
                            <td> ${path.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $PathFile.appendTo($("#properties"))
    
            });
    
            file.groupList.forEach((grp,index)=>{
                let $GroupFile =$(
                        `<tr class="clear">
                            <td>Group ${index + 1}
                            </td>
                            <td> children :${grp.children}
                            </td>
                            <td> ${grp.numAttr}
                            </td>
    
                        </tr>`
                    )
                    $GroupFile.appendTo($("#properties"))
    
            });
           

            for(let file of names){
            
                let $fileLogPannel =$(
                `<tr>
                    <td>
                        <a href=${file.name} download = ${file.name}>
                        <img src=${file.name} class="Fileinfo" id="imgS">
                        </a> 
                    </td>
                    <td>
                        <a href=${file.name} download = ${file.name}>
                        ${file.name}
                        </a>
                    </td>
                    <td>
                        ${file.size}
                    </td>
                    <td>
                        ${file.rects}
                    </td>
                    <td>
                        ${file.circs}
                    </td>
                    <td>
                        ${file.paths}
                    </td>
                    <td>
                        ${file.grps}
                    </td>
                </tr>
                `
                )
                $fileLogPannel.appendTo($("#panel"))
            }
            console.log('view panel done');

            for(let file of names){
                $('#file-options').append(
                    $('<option/>')
                    .text(file.name)
                );
                
            }
            for(let file of names){
                $('#file-form').append(
                    $('<option/>')
                    .text(file.name)
                );
                
            }
            for(let file of names){
                $('#file-scale').append(
                    $('<option/>')
                    .text(file.name)
                );
                
            }


            $('#RCscale').append(
                $('<option/>')
                
                .text("Rectangle")
            );
            $('#RCscale').append(
                $('<option/>')

                .text("Circle")
            );
            $('#createAdd').append(
                $('<button/>')
                .text("Add ")
            ); 
        },
        fail: function(error){
            console.log(error);
            alert("Failed");
        }
    });


    $('#rectcirc').append(
        $('<option/>')

        .text("Rectangle")
    );
    $('#rectcirc').append(
        $('<option/>')
        .text("Circle")
    );


    let scaling=$(
        `
        <tr>
        <td><label name="Rectangle">Rectangle  :</label></td>
        <td><input type="text" name="rect" value="1"></td>
        </tr>
        <tr>
        <td><label name="Circle">Circle  :</label></td>
        <td><input type="text" name="circ" value="1"></td>
        <td><input type="submit" name="btn" value="Submit"></td>    
        </tr>
        `
    )
    scaling.appendTo($("#scale"))  

    $(document).on("change","#rectcirc",function(){
        console.log('Success changing shape type');
        $('.shapeClear').each(function () {
            $(this).remove();
        });
        if ($(this).val() === 'Rectangle') {
            console.log('rect working');
            let rectShape= $(
                `
                
                <tr class ="shapeClear">
                    <td><label name="x">x  :</label></td>
                    <td><input type="text" name="x" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label name="y">y  :</label></td>
                    <td><input type="text" name="y" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>width  :</label></td>
                    <td><input type="text" name="width" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>height  :</label></td>
                    <td><input type="text" name="height" value="1cm"></td>
                </tr>
             
                `
            )
            rectShape.appendTo($("#Shape"))
            let $Btnn = $(
                `
                <button class="shapeClear">Submit</button>
                `
            )
            $Btnn.appendTo($("#Shape"))     
       
        } 
        else if ($(this).val() === 'Circle') {
            console.log('circle working');
            let circShape= $(
                `
                <tr class ="shapeClear">
                    <td><label>cx  :</label></td>
                    <td><input type="text" name="cx" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label >cy  :</label></td>
                    <td><input type="text" name="cy" value="1cm"></td>
                </tr>
                <tr class ="shapeClear">
                    <td><label>r  :</label></td>
                    <td><input type="text" name="r" value="1cm"></td>
                </tr>
                
                `
            )
            circShape.appendTo($("#Shape"))
            let $Btnn = $(
                `
                <button class="shapeClear">Submit</button>
                `
            )
            $Btnn.appendTo($("#Shape")) 

        }

    });



    $(document).on("change","#file-options",function(){
        console.log('file changed');
        $('#imgSi')
        .attr("src", $("#file-options option:selected").text());
        $('.clear').each(function () {
            $(this).remove();
        });
        $('.clean').each(function () {
            $(this).remove();
        });
        let file = getfile('#file-options');
        let $titdesc = $(
            `
            <tr class='clear width'>
            <td><label>Title  :</label></td>
            <td class='width'>
            <input type="text" name="title" value="${file.title}" placeholder="Enter Title"></td>
            </tr>
            <tr class='clear width'>
            <td class='clear'><label>Description  :</label></td>
            <td name="desc" class='width'>
            <input type="text" name="desc" value="${file.desc}" placeholder="Enter Title"></td>
            <td><input type="submit" name="tDbtn" value="Submit"></td>    
            </tr>
            `
        )
        $titdesc.appendTo($('#Titledescription'))

        file.rectList.forEach((rect,index)=>{
            let $RectFile =$(
                    `<tr class="clear">
                        <td>Rectangle ${index + 1}
                        </td>
                        <td>Upper left corner: x :${rect.x}${rect.units} , y:${rect.y}${rect.units},<br/>
                            width: ${rect.w}${rect.units} , height: ${rect.h}${rect.units} 
                        </td>
                        <td> ${rect.numAttr}
                        </td>

                    </tr>`
                )
                $RectFile.appendTo($("#properties"))
        });

        file.circList.forEach((circ,index)=>{
            let $CircFile =$(
                    `<tr class="clear">
                        <td>Circle ${index + 1}
                        </td>
                        <td>Centre: x :${circ.cx}${circ.units} , y:${circ.cy}${circ.units},<br/>
                            radius: ${circ.r}${circ.units} 
                        </td>
                        <td> ${circ.numAttr}
                        </td>

                    </tr>`
                )
                $CircFile.appendTo($("#properties"))
        });
        
        file.pathList.forEach((path,index)=>{
            let $PathFile =$(
                    `<tr class="clear">
                        <td>Path ${index +1}
                        </td>
                        <td> d :${path.d}
                        </td>
                        <td> ${path.numAttr}
                        </td>

                    </tr>`
                )
                $PathFile.appendTo($("#properties"))
        });

        file.groupList.forEach((grp,index)=>{
            let $GroupFile =$(
                    `<tr class="clear">
                        <td>Group ${index + 1}
                        </td>
                        <td> children :${grp.children}
                        </td>
                        <td> ${grp.numAttr}
                        </td>
                    </tr>`
                )
                $GroupFile.appendTo($("#properties"))
        });
    });

    $(document).on("click","#hide_attr",function(){
        $('.clean').each(function () {
            $(this).remove();
        });
    });


    $(document).on("click","#btn",function(){
        $('.clean').each(function () {
            $(this).remove();
        });
        let $hide_btn =$(
            `
            <button class="clean">Hide Attributes</button>
            `
        )
        $hide_btn.appendTo($("#hide_attr"))
        let file = getfile('#file-options');



        let $SVGatr =$(
            `<tr class="clean">
                <th >SVG 
                </th>
                <th>NAME
                </th>
                <th>VALUE
                </th>
            </tr>`
        )
        $SVGatr.appendTo($("#pp"))

        file.svgAttr.forEach((atr,count)=>{

            let $svgFile =$(
                `
                <tr class="clean">
                <td>
                </td>
                <td contenteditable='true'>${atr.name} 
                </td>
                <td contenteditable='true'>${atr.value}
                </td>
                </tr>
                `
            )
            $svgFile.appendTo($("#pp"))
        });

            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean showNotWork">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))

        file.rectList.forEach((rect,count)=>{

            let $RectFile =$(
                `<tr class="clean">
                    <th >Rectangle ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $RectFile.appendTo($("#pp"))

            let $RectRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>x 
                </td>
                <td contenteditable='true'>${rect.x}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>y 
                </td>
                <td contenteditable='true'>${rect.y}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>width 
                </td>
                <td contenteditable='true'>${rect.w}${rect.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>height 
                </td>
                <td contenteditable='true'>${rect.h}${rect.units}
                </td>
                </tr>
                `
            )
            $RectRequired.appendTo($("#pp"))

            file.rectAttr[count].forEach((atr,index2)=>{
            
                let $rectAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $rectAtr.appendTo($("#pp"))
            });

            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean showNotWork">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))

        });

        file.circList.forEach((circ,count)=>{
        
            let $CircFile =$(
                `<tr class="clean">
                    <th >Circle ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $CircFile.appendTo($("#pp"))

            let $CircRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>cx 
                </td>
                <td contenteditable='true'>${circ.cx}${circ.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>y 
                </td>
                <td contenteditable='true'>${circ.cy}${circ.units}
                </td>
                </tr>

                <tr class="clean">
                <td>
                </td>
                <td>r 
                </td>
                <td contenteditable='true'>${circ.r}${circ.units}
                </td>
                </tr>
                `
            )
            $CircRequired.appendTo($("#pp"))

            file.circAttr[count].forEach((atr,index2)=>{
                let $circAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $circAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean showNotWork">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))


        });
        file.pathList.forEach((path,count)=>{
       
            let $PathFile =$(
                `<tr class="clean">
                    <th >Path ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $PathFile.appendTo($("#pp"))

            let $PathRequired = $(
                `
                <tr class="clean">
                <td>
                </td>
                <td>data 
                </td>
                <td contenteditable='true'>${path.d}
                </td>
                </tr>
                `
            )
            $PathRequired.appendTo($("#pp"))

            file.pathAttr[count].forEach((atr,index2)=>{
                let $pathAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $pathAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean showNotWork">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))


        });
        file.groupList.forEach((group,count)=>{

            let $GroupFile =$(
                `<tr class="clean">
                    <th >Group ${count + 1}
                    </th>
                    <th>NAME
                    </th>
                    <th>VALUE
                    </th>
                </tr>`
            )
            $GroupFile.appendTo($("#pp"))

            file.groupAttr[count].forEach((atr,index2)=>{
                let $GroupAtr = $(
                    `<tr class="clean">
                    <td>
                    </td>
                    <td contenteditable='true'>${atr.name} 
                    </td>
                    <td contenteditable='true'>${atr.value}
                    </td>
                    </tr>
                    `
                )
                $GroupAtr.appendTo($("#pp"))
            });
            let $Btn = $(
                `<button class="clean displayAtr">Add Attribute</button>
                <button class="clean showNotWork">Submit</button>
                `
            )
            $Btn.appendTo($("#pp"))
        });

    });
    $(document).on('click', '.showNotWork', function () {
        alert("does not work for the back-end, Just used for front-end");
    });


    $(document).on('click', '.displayAtr', function () {
        console.log("can add attribute(frontend)");
        let temp = $(this);
        $(`<tr class="clean">
                <td></td>
                <td contenteditable="true">Attribute</td>
                <td contenteditable="true">Value</td>
            </tr>`).insertBefore(temp);
    });

    let Createsvg=$(
        `
        <tr>
        <td><label name="createsvg">File Name  :</label></td>
        <td><input type="text" name="fileData" value=""></td>
        </tr>
        <tr>
        <td><label name="title">title  :</label></td>
        <td><input type="text" name="tit" value=""></td>
        </tr>
        <tr>
        <td><label name="description">description  :</label></td>
        <td><input type="text" name="desc" value=""></td>
        </tr>
        <tr >
        <td><input type="submit" name="create" id="CreateBtn" value="Create SVG"></td>    
        <td ><input type="button" id="renu" value="Add Shape"></input></td>    
        </tr>
        </tr>
        `
    )
    Createsvg.appendTo($("#svg"))

    $(document).on("click","#CreateBtn",function(){
        alert("This is only used for frontend part, Does not create a new svg in backend");
    });

    $(document).on("click","#hide_atr",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
    });

    $(document).on("click","#renu",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
   
        let rc = $(
            `
            <tr class="clean_SVG">
            <td><button type="button" id="createrect">RECTANGLE</button></td>
            </tr>
            <tr class="clean_SVG">
            <td><button type="button" id="createcirc">CIRCLE</button></td>
            </tr>
            `
        )
        rc.appendTo($("#renuMain"))
    });

    $(document).on('click', '#renu', function ()
    {
    if (this.value=="Add Shape") {
        console.log("changing  ADD Shape to Hide Shape");
        this.value = "Hide";
        this.id = "hide_renu";
    
    }
    else{

        this.value = "Add Shape";
        this.id ="renu";
    }
        
    });
    $(document).on("click","#hide_renu",function(){
        $('.clean_SVG').each(function () {
            $(this).remove();
        });
        if (this.value=="Hide") {
            console.log("changing Hide button to ADD Shape");
            this.value = "Add Shape";
            this.id ="renu";
        }
        else{
            this.value = "Hide";
            this.id = "hide_renu";
        }
    });

    $(document).on('click', '#createrect', function () {
        let temp = $(this);
        $(`
        <tr class="clean_SVG">
        <th>Rectangle</th>
        </tr>
        <tr class="clean_SVG">
                    <td><label name="x">x  :</label></td>
                    <td><input type="text" name="x" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label name="y">y  :</label></td>
                    <td><input type="text" name="y" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label>width  :</label></td>
                    <td><input type="text" name="width" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                    <td><label>height  :</label></td>
                    <td><input type="text" name="height" value="1cm"></td>
                </tr>
                <tr class="clean_SVG">
                <td></td>
                <td><input type="button" name="height" class="createSvgSubmit" value="Submit"></td>
            </tr>    
        `).insertAfter(temp);
    });
    $(document).on('click', '#createcirc', function () {

        let temp = $(this);
        $(`  
        <tr class="clean_SVG">
        <th>Circle</th>
           </tr>     
        <tr class="clean_SVG">
            <td><label>cx  :</label></td>
            <td><input type="text" name="cx" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
            <td><label >cy  :</label></td>
            <td><input type="text" name="cy" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
            <td><label>r  :</label></td>
            <td><input type="text" name="r" value="1cm"></td>
        </tr>
        <tr class="clean_SVG">
        <td></td>
        <td><input type="button" name="height" class="createSvgSubmit" value="Submit"></td>
    </tr>
        `).insertAfter(temp);
    });
    function getfile(id){
        let option = $(id + " option:selected").text();
        for(let file of names){
            if(file.name == option){
                return file;
            }
        }
        return file[0];
    }

    $(document).on("click",".createSvgSubmit",function(){
        alert("This is only used for frontend part, Does not Submit data in The backend");
    });

        
    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#someform').submit(function(e){
        $('#blah').html("Form has data: "+$('#entryBox').val());
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
        });
    });


});

