// Gets most spreadsheet entry

const SHEET_ID = "1Qyy25yesqFlnQmXB5tJPd1JoPqWuW3Znv48zgeDISZI";
const ACCESS_TOKEN = "ya29.a0AfH6SMCXNDwh4W6utUxqJ76Oa9uVmADUVoj5NDlJyjH9eXVfbQUtghHUB_oFjGHmY6mslwQe5y93paz-dpxZdZeBZ-xjFoRLQf7kxG9mM-AKfBAepemCtSzTun4pWWUkrKLxrL9M1c6a1EHdSe-VMt9Yozg66XVA1hQ";

let url = `https://sheets.googleapis.com/v4/spreadsheets/${SHEET_ID}/values/A2:D2`;

getSheetValues = async () => {
    try {
        await fetch(url,
            {
                headers: {
                    "Content-Type": "application/json",
                    Authorization: `Bearer ${ACCESS_TOKEN}`
                }
            })
            .then(resp => resp.json())
            .then((data) => {
                console.log(data);

                // Creates a new paragraph elemnt inside the div binStatus
                var parentElement = document.getElementById('binStatus');
                var statuspCreate = document.createElement('p');
                var statusp = parentElement.appendChild(statuspCreate);

                // Makes a var pointing to the values of the array returned from the fetch
                var vals = data.values[0];

                // If the 3rd and 4th elemnt of the values (half and full) are
                // Both 0, then the nin is full, if half is 0 then it is half full
                // If both are 1, then it is empty
                if (vals[2] >= 0 && vals[2] <= 1)
                {
                    statusp.innerHTML = `Your bin is ${vals[2] * 100}% full`;
                }
                else
                {
                    statusp.innerHTML = "Error in bin amount full";
                }
            })
     }
    catch(err)
    {
        console.error(err);
    }
}

getSheetValues();